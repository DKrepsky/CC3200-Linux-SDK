//*****************************************************************************
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************


//*****************************************************************************
//
// Application Name     - File Download
// Application Overview - The objective of this sample code is to demonstrate
//                        how to connect to a server to download a file and save
//                        it on the serial flash. This scheme can be used by
//                        App developer to update any file over the network.
// Application Details  -
// http://processors.wiki.ti.com/index.php/CC32xx_File_Download_Application
// or
// docs\examples\CC32xx_File_Download_Application.pdf
//
//*****************************************************************************


#include <string.h>

// SimpleLink includes
#include "simplelink.h"

// driverlib includes
#include "hw_ints.h"
#include "hw_types.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"
#include "utils.h"
#include "interrupt.h"

// common interface includes
#include "uart_if.h"
#include "common.h"
#include "pinmux.h"


#define APPLICATION_VERSION "1.1.0"
#define APP_NAME            "File Download"

#define PREFIX_BUFFER    "GET /lit/er/swrz044b/swrz044b.pdf"
#define POST_BUFFER      " HTTP/1.1\nHost:www.ti.com\nAccept: text/html, application/xhtml+xml, */*\n\n"
#define HOST_NAME        "www.ti.com"

#define HTTP_FILE_NOT_FOUND    "404 Not Found" /* HTTP file not found response */
#define HTTP_STATUS_OK         "200 OK"  /* HTTP status ok response */
#define HTTP_CONTENT_LENGTH    "Content-Length:"  /* HTTP content length header */
#define HTTP_TRANSFER_ENCODING "Transfer-Encoding:" /* HTTP transfer encoding header */
#define HTTP_ENCODING_CHUNKED  "chunked" /* HTTP transfer encoding header value */
#define HTTP_CONNECTION        "Connection:" /* HTTP Connection header */
#define HTTP_CONNECTION_CLOSE  "close"  /* HTTP Connection header value */

#define DNS_RETRY           5 /* No of DNS tries */
#define HTTP_END_OF_HEADER  "\r\n\r\n"  /* string marking the end of headers in response */
#define SIZE_40K            40960  /* Serial flash file size 40 KB */

#define READ_SIZE          1450
#define MAX_BUFF_SIZE      1460

// Temporary file to store the downloaded file
#define TEMP_FILE_NAME "cc3000_module_temp.pdf"
// File on the serial flash to be replaced
#define FILE_NAME "cc3000_module.pdf"

// Application specific status/error codes
typedef enum{
 /* Choosing this number to avoid overlap with host-driver's error codes */
    DEVICE_NOT_IN_STATION_MODE = -0x7D0,       
    DEVICE_START_FAILED = DEVICE_NOT_IN_STATION_MODE - 1,
    INVALID_HEX_STRING = DEVICE_START_FAILED - 1,
    TCP_RECV_ERROR = INVALID_HEX_STRING - 1,
    TCP_SEND_ERROR = TCP_RECV_ERROR - 1,
    FILE_NOT_FOUND_ERROR = TCP_SEND_ERROR - 1,
    INVALID_SERVER_RESPONSE = FILE_NOT_FOUND_ERROR - 1,
    FORMAT_NOT_SUPPORTED = INVALID_SERVER_RESPONSE - 1,
    FILE_OPEN_FAILED = FORMAT_NOT_SUPPORTED - 1,
    FILE_WRITE_ERROR = FILE_OPEN_FAILED - 1,
    INVALID_FILE = FILE_WRITE_ERROR - 1,
    SERVER_CONNECTION_FAILED = INVALID_FILE - 1,
    GET_HOST_IP_FAILED = SERVER_CONNECTION_FAILED  - 1,
    
    STATUS_CODE_MAX = -0xBB8
}e_AppStatusCodes;

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
unsigned long  g_ulStatus = 0;//SimpleLink Status
unsigned long  g_ulDestinationIP; // IP address of destination server
unsigned long  g_ulGatewayIP = 0; //Network Gateway IP address
unsigned char  g_ucConnectionSSID[SSID_LEN_MAX+1]; //Connection SSID
unsigned char  g_ucConnectionBSSID[BSSID_LEN_MAX]; //Connection BSSID
int g_iSockID = 0;
unsigned char g_buff[MAX_BUFF_SIZE+1];
long bytesReceived = 0; // variable to store the file size

#if defined(ccs) || defined(gcc)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif
//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************



//*****************************************************************************
// SimpleLink Asynchronous Event Handlers -- Start
//*****************************************************************************


//*****************************************************************************
//
//! \brief The Function Handles WLAN Events
//!
//! \param[in]  pWlanEvent - Pointer to WLAN Event Info
//!
//! \return None
//!
//*****************************************************************************
void SimpleLinkWlanEventHandler(SlWlanEvent_t *pWlanEvent)
{
    switch(pWlanEvent->Event)
    {
        case SL_WLAN_CONNECT_EVENT:
        {
            SET_STATUS_BIT(g_ulStatus, STATUS_BIT_CONNECTION);

            //
            // Information about the connected AP (like name, MAC etc) will be
            // available in 'slWlanConnectAsyncResponse_t'-Applications
            // can use it if required
            //
            //  slWlanConnectAsyncResponse_t *pEventData = NULL;
            // pEventData = &pWlanEvent->EventData.STAandP2PModeWlanConnected;
            //

            // Copy new connection SSID and BSSID to global parameters
            memcpy(g_ucConnectionSSID,pWlanEvent->EventData.
                   STAandP2PModeWlanConnected.ssid_name,
                   pWlanEvent->EventData.STAandP2PModeWlanConnected.ssid_len);
            memcpy(g_ucConnectionBSSID,
                   pWlanEvent->EventData.STAandP2PModeWlanConnected.bssid,
                   SL_BSSID_LENGTH);

            UART_PRINT("[WLAN EVENT] STA Connected to the AP: %s ,"
                            " BSSID: %x:%x:%x:%x:%x:%x\n\r",
                      g_ucConnectionSSID,g_ucConnectionBSSID[0],
                      g_ucConnectionBSSID[1],g_ucConnectionBSSID[2],
                      g_ucConnectionBSSID[3],g_ucConnectionBSSID[4],
                      g_ucConnectionBSSID[5]);
        }
        break;

        case SL_WLAN_DISCONNECT_EVENT:
        {
            slWlanConnectAsyncResponse_t*  pEventData = NULL;

            CLR_STATUS_BIT(g_ulStatus, STATUS_BIT_CONNECTION);
            CLR_STATUS_BIT(g_ulStatus, STATUS_BIT_IP_AQUIRED);

            pEventData = &pWlanEvent->EventData.STAandP2PModeDisconnected;

            // If the user has initiated 'Disconnect' request,
            //'reason_code' is SL_USER_INITIATED_DISCONNECTION
            if(SL_USER_INITIATED_DISCONNECTION == pEventData->reason_code)
            {
                UART_PRINT("[WLAN EVENT]Device disconnected from the AP: %s,"
                "BSSID: %x:%x:%x:%x:%x:%x on application's request \n\r",
                           g_ucConnectionSSID,g_ucConnectionBSSID[0],
                           g_ucConnectionBSSID[1],g_ucConnectionBSSID[2],
                           g_ucConnectionBSSID[3],g_ucConnectionBSSID[4],
                           g_ucConnectionBSSID[5]);
            }
            else
            {
                UART_PRINT("[WLAN ERROR]Device disconnected from the AP AP: %s,"
                "BSSID: %x:%x:%x:%x:%x:%x on an ERROR..!! \n\r",
                           g_ucConnectionSSID,g_ucConnectionBSSID[0],
                           g_ucConnectionBSSID[1],g_ucConnectionBSSID[2],
                           g_ucConnectionBSSID[3],g_ucConnectionBSSID[4],
                           g_ucConnectionBSSID[5]);
            }
            memset(g_ucConnectionSSID,0,sizeof(g_ucConnectionSSID));
            memset(g_ucConnectionBSSID,0,sizeof(g_ucConnectionBSSID));
        }
        break;

        default:
        {
            UART_PRINT("[WLAN EVENT] Unexpected event [0x%x]\n\r",
                       pWlanEvent->Event);
        }
        break;
    }
}

//*****************************************************************************
//
//! \brief This function handles network events such as IP acquisition, IP
//!           leased, IP released etc.
//!
//! \param[in]  pNetAppEvent - Pointer to NetApp Event Info
//!
//! \return None
//!
//*****************************************************************************
void SimpleLinkNetAppEventHandler(SlNetAppEvent_t *pNetAppEvent)
{
    switch(pNetAppEvent->Event)
    {
        case SL_NETAPP_IPV4_IPACQUIRED_EVENT:
        {
            SlIpV4AcquiredAsync_t *pEventData = NULL;

            SET_STATUS_BIT(g_ulStatus, STATUS_BIT_IP_AQUIRED);

            //Ip Acquired Event Data
            pEventData = &pNetAppEvent->EventData.ipAcquiredV4;

            //Gateway IP address
            g_ulGatewayIP = pEventData->gateway;

            UART_PRINT("[NETAPP EVENT] IP Acquired: IP=%d.%d.%d.%d , "
            "Gateway=%d.%d.%d.%d\n\r",
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.ip,3),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.ip,2),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.ip,1),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.ip,0),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.gateway,3),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.gateway,2),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.gateway,1),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.gateway,0));
        }
        break;

        default:
        {
            UART_PRINT("[NETAPP EVENT] Unexpected event [0x%x] \n\r",
                       pNetAppEvent->Event);
        }
        break;
    }
}


//*****************************************************************************
//
//! \brief This function handles HTTP server events
//!
//! \param[in]  pServerEvent - Contains the relevant event information
//! \param[in]    pServerResponse - Should be filled by the user with the
//!                                      relevant response information
//!
//! \return None
//!
//****************************************************************************
void SimpleLinkHttpServerCallback(SlHttpServerEvent_t *pHttpEvent,
                                  SlHttpServerResponse_t *pHttpResponse)
{
    // Unused in this application
}

//*****************************************************************************
//
//! \brief This function handles General Events
//!
//! \param[in]     pDevEvent - Pointer to General Event Info
//!
//! \return None
//!
//*****************************************************************************
void SimpleLinkGeneralEventHandler(SlDeviceEvent_t *pDevEvent)
{
    //
    // Most of the general errors are not FATAL are are to be handled
    // appropriately by the application
    //
    UART_PRINT("[GENERAL EVENT] - ID=[%d] Sender=[%d]\n\n",
               pDevEvent->EventData.deviceEvent.status,
               pDevEvent->EventData.deviceEvent.sender);
}


//*****************************************************************************
//
//! This function handles socket events indication
//!
//! \param[in]      pSock - Pointer to Socket Event Info
//!
//! \return None
//!
//*****************************************************************************
void SimpleLinkSockEventHandler(SlSockEvent_t *pSock)
{
    //
    // This application doesn't work w/ socket - Events are not expected
    //
       switch( pSock->Event )
    {
        case SL_SOCKET_TX_FAILED_EVENT:
            switch( pSock->EventData.status )
            {
                case SL_ECLOSE:
                    UART_PRINT("[SOCK ERROR] - close socket (%d) operation "
                    "failed to transmit all queued packets\n\n",
                           pSock->EventData.sd);
                    break;
                default:
                    UART_PRINT("[SOCK ERROR] - TX FAILED : socket %d , reason"
                        "(%d) \n\n",
                           pSock->EventData.sd, pSock->EventData.status);
            }
            break;

        default:
            UART_PRINT("[SOCK EVENT] - Unexpected Event [%x0x]\n\n",pSock->Event);
    }
}


//*****************************************************************************
// SimpleLink Asynchronous Event Handlers -- End
//*****************************************************************************



//*****************************************************************************
//
//! \brief This function initializes the application variables
//!
//! \param    None
//!
//! \return None
//!
//*****************************************************************************
static void InitializeAppVariables()
{
    g_ulStatus = 0;
    g_ulGatewayIP = 0;
    memset(g_ucConnectionSSID,0,sizeof(g_ucConnectionSSID));
    memset(g_ucConnectionBSSID,0,sizeof(g_ucConnectionBSSID));
}


//*****************************************************************************
//! \brief This function puts the device in its default state. It:
//!           - Set the mode to STATION
//!           - Configures connection policy to Auto and AutoSmartConfig
//!           - Deletes all the stored profiles
//!           - Enables DHCP
//!           - Disables Scan policy
//!           - Sets Tx power to maximum
//!           - Sets power policy to normal
//!           - Unregister mDNS services
//!           - Remove all filters
//!
//! \param   none
//! \return  On success, zero is returned. On error, negative is returned
//*****************************************************************************
static long ConfigureSimpleLinkToDefaultState()
{
    SlVersionFull   ver = {0};
    _WlanRxFilterOperationCommandBuff_t  RxFilterIdMask = {0};

    unsigned char ucVal = 1;
    unsigned char ucConfigOpt = 0;
    unsigned char ucConfigLen = 0;
    unsigned char ucPower = 0;

    long lRetVal = -1;
    long lMode = -1;

    lMode = sl_Start(0, 0, 0);
    ASSERT_ON_ERROR(lMode);

    // If the device is not in station-mode, try configuring it in station-mode 
    if (ROLE_STA != lMode)
    {
        if (ROLE_AP == lMode)
        {
            // If the device is in AP mode, we need to wait for this event 
            // before doing anything 
            while(!IS_IP_ACQUIRED(g_ulStatus))
            {
#ifndef SL_PLATFORM_MULTI_THREADED
              _SlNonOsMainLoopTask(); 
#endif
            }
        }

        // Switch to STA role and restart 
        lRetVal = sl_WlanSetMode(ROLE_STA);
        ASSERT_ON_ERROR(lRetVal);

        lRetVal = sl_Stop(0xFF);
        ASSERT_ON_ERROR(lRetVal);

        lRetVal = sl_Start(0, 0, 0);
        ASSERT_ON_ERROR(lRetVal);

        // Check if the device is in station again 
        if (ROLE_STA != lRetVal)
        {
            // We don't want to proceed if the device is not coming up in STA-mode 
            return DEVICE_NOT_IN_STATION_MODE;
        }
    }
    
    // Get the device's version-information
    ucConfigOpt = SL_DEVICE_GENERAL_VERSION;
    ucConfigLen = sizeof(ver);
    lRetVal = sl_DevGet(SL_DEVICE_GENERAL_CONFIGURATION, &ucConfigOpt, 
                                &ucConfigLen, (unsigned char *)(&ver));
    ASSERT_ON_ERROR(lRetVal);
    
    UART_PRINT("Host Driver Version: %s\n\r",SL_DRIVER_VERSION);
    UART_PRINT("Build Version %d.%d.%d.%d.31.%d.%d.%d.%d.%d.%d.%d.%d\n\r",
    ver.NwpVersion[0],ver.NwpVersion[1],ver.NwpVersion[2],ver.NwpVersion[3],
    ver.ChipFwAndPhyVersion.FwVersion[0],ver.ChipFwAndPhyVersion.FwVersion[1],
    ver.ChipFwAndPhyVersion.FwVersion[2],ver.ChipFwAndPhyVersion.FwVersion[3],
    ver.ChipFwAndPhyVersion.PhyVersion[0],ver.ChipFwAndPhyVersion.PhyVersion[1],
    ver.ChipFwAndPhyVersion.PhyVersion[2],ver.ChipFwAndPhyVersion.PhyVersion[3]);

    // Set connection policy to Auto + SmartConfig 
    //      (Device's default connection policy)
    lRetVal = sl_WlanPolicySet(SL_POLICY_CONNECTION, 
                                SL_CONNECTION_POLICY(1, 0, 0, 0, 1), NULL, 0);
    ASSERT_ON_ERROR(lRetVal);

    // Remove all profiles
    lRetVal = sl_WlanProfileDel(0xFF);
    ASSERT_ON_ERROR(lRetVal);

    //
    // Device in station-mode. Disconnect previous connection if any
    // The function returns 0 if 'Disconnected done', negative number if already
    // disconnected Wait for 'disconnection' event if 0 is returned, Ignore 
    // other return-codes
    //
    lRetVal = sl_WlanDisconnect();
    if(0 == lRetVal)
    {
        // Wait
        while(IS_CONNECTED(g_ulStatus))
        {
#ifndef SL_PLATFORM_MULTI_THREADED
              _SlNonOsMainLoopTask(); 
#endif
        }
    }

    // Enable DHCP client
    lRetVal = sl_NetCfgSet(SL_IPV4_STA_P2P_CL_DHCP_ENABLE,1,1,&ucVal);
    ASSERT_ON_ERROR(lRetVal);

    // Disable scan
    ucConfigOpt = SL_SCAN_POLICY(0);
    lRetVal = sl_WlanPolicySet(SL_POLICY_SCAN , ucConfigOpt, NULL, 0);
    ASSERT_ON_ERROR(lRetVal);

    // Set Tx power level for station mode
    // Number between 0-15, as dB offset from max power - 0 will set max power
    ucPower = 0;
    lRetVal = sl_WlanSet(SL_WLAN_CFG_GENERAL_PARAM_ID, 
            WLAN_GENERAL_PARAM_OPT_STA_TX_POWER, 1, (unsigned char *)&ucPower);
    ASSERT_ON_ERROR(lRetVal);

    // Set PM policy to normal
    lRetVal = sl_WlanPolicySet(SL_POLICY_PM , SL_NORMAL_POLICY, NULL, 0);
    ASSERT_ON_ERROR(lRetVal);

    // Unregister mDNS services
    lRetVal = sl_NetAppMDNSUnRegisterService(0, 0);
    ASSERT_ON_ERROR(lRetVal);

    // Remove  all 64 filters (8*8)
    memset(RxFilterIdMask.FilterIdMask, 0xFF, 8);
    lRetVal = sl_WlanRxFilterSet(SL_REMOVE_RX_FILTER, (_u8 *)&RxFilterIdMask,
                       sizeof(_WlanRxFilterOperationCommandBuff_t));
    ASSERT_ON_ERROR(lRetVal);


    lRetVal = sl_Stop(SL_STOP_TIMEOUT);
    ASSERT_ON_ERROR(lRetVal);

    InitializeAppVariables();

    return SUCCESS;
}



//****************************************************************************
//
//! \brief Connecting to a WLAN Accesspoint
//!
//!  This function connects to the required AP (SSID_NAME) with Security
//!  parameters specified in te form of macros at the top of this file
//!
//! \param  Status value
//!
//! \return  None
//!
//! \warning    If the WLAN connection fails or we don't aquire an IP
//!            address, It will be stuck in this function forever.
//
//****************************************************************************
static long WlanConnect()
{
    SlSecParams_t secParams = {0};
    long lRetVal = 0;

    secParams.Key = (signed char *)SECURITY_KEY;
    secParams.KeyLen = strlen(SECURITY_KEY);
    secParams.Type = SECURITY_TYPE;

    lRetVal = sl_WlanConnect((signed char *)SSID_NAME,
                           strlen((const char *)SSID_NAME), 0, &secParams, 0);
    ASSERT_ON_ERROR(lRetVal);

    // Wait for WLAN Event
    while((!IS_CONNECTED(g_ulStatus)) || (!IS_IP_ACQUIRED(g_ulStatus)))
    {
        // wait till connects to an AP
        _SlNonOsMainLoopTask();
    }

    return SUCCESS;

}

//****************************************************************************
//
//! Create an endpoint for communication and initiate connection on socket.*/
//!
//! \brief Create connection with server
//!
//! This function opens a socket and create the endpoint communication with server
//!
//! \param[in]      DestinationIP - IP address of the server
//!
//! \return         socket id for success and negative for error
//
//****************************************************************************
int CreateConnection(unsigned long DestinationIP)
{
    SlSockAddrIn_t  Addr;
    int             Status = 0;
    int             AddrSize = 0;
    int             SockID = 0;

    Addr.sin_family = SL_AF_INET;
    Addr.sin_port = sl_Htons(80);
    Addr.sin_addr.s_addr = sl_Htonl(DestinationIP);

    AddrSize = sizeof(SlSockAddrIn_t);

    SockID = sl_Socket(SL_AF_INET,SL_SOCK_STREAM, 0);
    ASSERT_ON_ERROR(SockID);

    Status = sl_Connect(SockID, ( SlSockAddr_t *)&Addr, AddrSize);
    if( Status < 0 )
    {
        /* Error */
        sl_Close(SockID);
        ASSERT_ON_ERROR(Status);
    }
    return SockID;
}

//****************************************************************************
//
//!
//! \brief Convert hex to decimal base
//!
//! \param[in]      ptr - pointer to string containing number in hex
//!
//! \return         number in decimal base
//!
//
//****************************************************************************
signed long hexToi(unsigned char *ptr)
{
    unsigned long result = 0;
    int idx = 0;
    unsigned int len = strlen((const char *)ptr);

    // convert characters to upper case
    for(idx = 0; ptr[idx] != '\0'; ++idx)
    {
        if( (ptr[idx] >= 'a') &&
            (ptr[idx] <= 'f') )
        {
            /* Change case - ASCII 'a' = 97, 'A' = 65 => 97-65 = 32 */
            ptr[idx] -= 32;         
        }
    }

    for(idx = 0; ptr[idx] != '\0'; ++idx)
    {
        if(ptr[idx] >= '0' && ptr[idx] <= '9')
        {
            /* Converting '0' to '9' to their decimal value */
            result += (ptr[idx] - '0') * (1 << (4 * (len - 1 - idx)));
        }
        else if(ptr[idx] >= 'A' && ptr[idx] <= 'F')
        {
            /* Converting hex 'A' to 'F' to their decimal value */
            /* .i.e. 'A' - 55 = 10, 'F' - 55 = 15 */
            result += (ptr[idx] - 55) * (1 << (4 * (len -1 - idx))); 
        }
        else
        {
            ASSERT_ON_ERROR(INVALID_HEX_STRING);
        }
    }

    return result;
}

//****************************************************************************
//
//! \brief Calculate the file chunk size
//!
//! \param[in]      len - pointer to length of the data in the buffer
//! \param[in]      p_Buff - pointer to ponter of buffer containing data
//! \param[out]     chunk_size - pointer to variable containing chunk size
//!
//! \return         0 for success, -ve for error
//
//****************************************************************************
int GetChunkSize(int *len, unsigned char **p_Buff, unsigned long *chunk_size)
{
    int           idx = 0;
    unsigned char lenBuff[10];
    signed long lRetVal = -1;

    idx = 0;
    memset(lenBuff, 0, 10);
    while(*len >= 0 && **p_Buff != 13) /* check for <CR> */
    {
        if(*len == 0)
        {
            memset(g_buff, 0, sizeof(g_buff));
            *len = sl_Recv(g_iSockID, &g_buff[0], MAX_BUFF_SIZE, 0);
            if(*len <= 0)
                ASSERT_ON_ERROR(TCP_RECV_ERROR);

            *p_Buff = g_buff;
        }
        lenBuff[idx] = **p_Buff;
        idx++;
        (*p_Buff)++;
        (*len)--;
    }
    (*p_Buff) += 2; // skip <CR><LF>
    (*len) -= 2;
    lRetVal = hexToi(lenBuff);
    if(lRetVal < 0)
    {
        ASSERT_ON_ERROR(INVALID_HEX_STRING);
    }
    else
    {
        *chunk_size = lRetVal;
    }

    return SUCCESS;
}

//****************************************************************************
//
//! \brief Obtain the file from the server
//!
//!  This function requests the file from the server and save it on serial flash.
//!  To request a different file for different user needs to modify the
//!  PREFIX_BUFFER and POST_BUFFER macros.
//!
//! \param[in]      None
//!
//! \return         0 for success and negative for error
//
//****************************************************************************
int GetData()
{
    int           transfer_len = 0;
    long          lRetVal = 0;
    long          fileHandle = -1;
    unsigned long Token = 0;
    unsigned char *pBuff = 0;
    char          eof_detected = 0;
    unsigned long recv_size = 0;
    unsigned char isChunked = 0;

    UART_PRINT("Start downloading the file\r\n");

    memset(g_buff, 0, sizeof(g_buff));

    // Puts together the HTTP GET string.
    strcpy((char *)g_buff, PREFIX_BUFFER);

    strcat((char *)g_buff, POST_BUFFER);


    // Send the HTTP GET string to the opened TCP/IP socket.
    transfer_len = sl_Send(g_iSockID, g_buff, strlen((const char *)g_buff), 0);

    if (transfer_len < 0)
    {
        // error
        ASSERT_ON_ERROR(TCP_SEND_ERROR);
    }

    memset(g_buff, 0, sizeof(g_buff));

    // get the reply from the server in buffer.
    transfer_len = sl_Recv(g_iSockID, &g_buff[0], MAX_BUFF_SIZE, 0);

    if(transfer_len <= 0)
    {
        ASSERT_ON_ERROR(TCP_RECV_ERROR);
    }

    // Check for 404 return code
    if(strstr((const char *)g_buff, HTTP_FILE_NOT_FOUND) != 0)
    {
        ASSERT_ON_ERROR(FILE_NOT_FOUND_ERROR);
    }

    // if not "200 OK" return error
    if(strstr((const char *)g_buff, HTTP_STATUS_OK) == 0)
    {
        ASSERT_ON_ERROR(INVALID_SERVER_RESPONSE);
    }

    // check if content length is transfered with headers
    pBuff = (unsigned char *)strstr((const char *)g_buff, HTTP_CONTENT_LENGTH);
    if(pBuff != 0)
    {
        // not supported
        ASSERT_ON_ERROR(FORMAT_NOT_SUPPORTED);
    }

    // Check if data is chunked
    pBuff = (unsigned char *)strstr((const char *)g_buff, HTTP_TRANSFER_ENCODING);
    if(pBuff != 0)
    {
        pBuff += strlen(HTTP_TRANSFER_ENCODING);
        while(*pBuff == 32)
            pBuff++;

        if(memcmp(pBuff, HTTP_ENCODING_CHUNKED, strlen(HTTP_ENCODING_CHUNKED)) == 0)
        {
            recv_size = 0;
            isChunked = 1;
        }
    }
    else
    {
        // Check if connection will be closed by after sending data
        // In this method the content length is not received and end of
        // connection marks the end of data
        pBuff = (unsigned char *)strstr((const char *)g_buff, HTTP_CONNECTION);
        if(pBuff != 0)
        {
            pBuff += strlen(HTTP_CONNECTION);
            while(*pBuff == 32)
                pBuff++;

            if(memcmp(pBuff, HTTP_ENCODING_CHUNKED, strlen(HTTP_CONNECTION_CLOSE)) == 0)
            {
                // not supported
                ASSERT_ON_ERROR(FORMAT_NOT_SUPPORTED);
            }
        }
    }

    // "\r\n\r\n" marks the end of headers
    pBuff = (unsigned char *)strstr((const char *)g_buff, HTTP_END_OF_HEADER);
    if(pBuff == 0)
    {
        ASSERT_ON_ERROR(INVALID_SERVER_RESPONSE);
    }
    // Increment by 4 to skip "\r\n\r\n"
    pBuff += 4;

    // Adjust buffer data length for header size
    transfer_len -= (pBuff - g_buff);

    // If data in chunked format, calculate the chunk size
    if(isChunked == 1)
    {
        lRetVal = GetChunkSize(&transfer_len, &pBuff, &recv_size);
        ASSERT_ON_ERROR(lRetVal);
    }

    /* Open file to save the downloaded file */
    lRetVal = sl_FsOpen((_u8 *)FILE_NAME,
                       FS_MODE_OPEN_WRITE, &Token, &fileHandle);
    if(lRetVal < 0)
    {
        // File Doesn't exit create a new of 40 KB file
        lRetVal = sl_FsOpen((unsigned char *)FILE_NAME, \
                           FS_MODE_OPEN_CREATE(SIZE_40K, \
                           _FS_FILE_OPEN_FLAG_COMMIT|_FS_FILE_PUBLIC_WRITE),
                           &Token, &fileHandle);
        ASSERT_ON_ERROR(lRetVal);

    }

    while (0 < transfer_len)
    {
        // For chunked data recv_size contains the chunk size to be received
        if(recv_size <= transfer_len)
        {
            // write the recv_size
            lRetVal = sl_FsWrite(fileHandle, bytesReceived,
                    (unsigned char *)pBuff, recv_size);
            if(lRetVal < recv_size)
            {
                UART_PRINT("Failed during writing the file, Error-code: %d\r\n", \
                            FILE_WRITE_ERROR);
                /* Close file without saving */
                lRetVal = sl_FsClose(fileHandle, 0, (unsigned char*) "A", 1);
                return lRetVal;
            }
            transfer_len -= recv_size;
            bytesReceived +=recv_size;
            pBuff += recv_size;
            recv_size = 0;

            if(isChunked == 1)
            {
                // if data in chunked format calculate next chunk size
                pBuff += 2; // 2 bytes for <CR> <LF>
                transfer_len -= 2;

                if(GetChunkSize(&transfer_len, &pBuff, &recv_size) < 0)
                {
                    // Error
                    break;
                }

                // if next chunk size is zero we have received the complete file
                if(recv_size == 0)
                {
                    eof_detected = 1;
                    break;
                }

                if(recv_size < transfer_len)
                {
                    // Code will enter this section if the new chunk size is
                    // less than the transfer size. This will the last chunk of
                    // file received
                    lRetVal =sl_FsWrite(fileHandle, bytesReceived,
                            (unsigned char *)pBuff, recv_size);
                    if(lRetVal < recv_size)
                    {
                        UART_PRINT("Failed during writing the file, " \
                                    "Error-code: %d\r\n", FILE_WRITE_ERROR);
                        /* Close file without saving */
                        lRetVal = sl_FsClose(fileHandle, 0, \
                                                (unsigned char*)"A", 1);
                        return FILE_WRITE_ERROR;
                    }
                    transfer_len -= recv_size;
                    bytesReceived +=recv_size;
                    pBuff += recv_size;
                    recv_size = 0;

                    pBuff += 2; // 2bytes for <CR> <LF>
                    transfer_len -= 2;

                    // Calculate the next chunk size, should be zero
                    if(GetChunkSize(&transfer_len, &pBuff, &recv_size) < 0)
                    {
                        // Error
                        break;
                    }

                    // if next chunk size is non zero error
                    if(recv_size != 0)
                    {
                        // Error
                        break;
                    }
                    eof_detected = 1;
                    break;
                }
                else
                {
                    // write data on the file
                    lRetVal =sl_FsWrite(fileHandle, bytesReceived,
                            (unsigned char *)pBuff, transfer_len);
                    if(lRetVal < transfer_len)
                    {
                        UART_PRINT("Failed during writing the file, " \
                                    "Error-code: %d\r\n", FILE_WRITE_ERROR);
                        /* Close file without saving */
                        lRetVal = sl_FsClose(fileHandle, 0, \
                                                (unsigned char*)"A", 1);
                        return FILE_WRITE_ERROR;
                    }
                    recv_size -= transfer_len;
                    bytesReceived +=transfer_len;
                }
            }
            // complete file received exit
            if(recv_size == 0)
            {
                eof_detected = 1;
                break;
            }
        }
        else
        {
            // write data on the file
            lRetVal = sl_FsWrite(fileHandle, bytesReceived,
                                 (unsigned char *)pBuff, transfer_len);
            if (lRetVal < 0)
            {
                UART_PRINT("Failed during writing the file, Error-code: " \
                            "%d\r\n", FILE_WRITE_ERROR);
                /* Close file without saving */
                lRetVal = sl_FsClose(fileHandle, 0, (unsigned char*)"A", 1);
                return FILE_WRITE_ERROR;
            }
            bytesReceived +=transfer_len;
            recv_size -= transfer_len;
        }

        memset(g_buff, 0, sizeof(g_buff));

        transfer_len = sl_Recv(g_iSockID, &g_buff[0], MAX_BUFF_SIZE, 0);
        if(transfer_len <= 0)
            return TCP_RECV_ERROR;

        pBuff = g_buff;
    }

    //
    // If user file has checksum which can be used to verify the temporary
    // file then file should be verified
    // In case of invalid file (FILE_NAME) should be closed without saving to
    // recover the previous version of file
    //
    if(0 > transfer_len || eof_detected == 0)
    {
        /* Close file without saving */
        lRetVal = sl_FsClose(fileHandle, 0, (unsigned char*)"A", 1);
        UART_PRINT("Failed while File Download, Error-code: %d\r\n", \
                            INVALID_FILE);
        return INVALID_FILE;
    }
    else
    {
        /* Save and close file */
        lRetVal = sl_FsClose(fileHandle, 0, 0, 0);
        ASSERT_ON_ERROR(lRetVal);
    }

    return SUCCESS;
}

//*****************************************************************************
//
//! Function to connect to server and download the requested file
//!
//! \param  none
//!
//! \return Error-code or SUCCESS
//!
//*****************************************************************************
static long ServerFileDownload()
{
    long lRetVal = -1;

    //
    // Following function configure the device to default state by cleaning
    // the persistent settings stored in NVMEM (viz. connection profiles &
    // policies, power policy etc)
    //
    // Applications may choose to skip this step if the developer is sure
    // that the device is in its desired state at start of applicaton
    //
    // Note that all profiles and persistent settings that were done on the
    // device will be lost
    //
    lRetVal = ConfigureSimpleLinkToDefaultState();
    if(lRetVal < 0)
    {
        if (DEVICE_NOT_IN_STATION_MODE == lRetVal)
        {
            UART_PRINT("Failed to configure the device in its default state, "
                            "Error-code: %d\n\r", DEVICE_NOT_IN_STATION_MODE);
        }

        LOOP_FOREVER();
    }

    UART_PRINT("Device is configured in default state \n\r");

    //
    // Assumption is that the device is configured in station mode already
    // and it is in its default state
    //
    lRetVal = sl_Start(0, 0, 0);
    if (lRetVal < 0 || ROLE_STA != lRetVal)
    {
        ASSERT_ON_ERROR(DEVICE_START_FAILED);
    }

    UART_PRINT("Device started as STATION \n\r");

    // Connecting to WLAN AP - Set with static parameters defined at the top
    // After this call we will be connected and have IP address
    lRetVal = WlanConnect();

    UART_PRINT("Connected to the AP: %s\r\n", SSID_NAME);

    lRetVal = sl_NetAppDnsGetHostByName((signed char *)HOST_NAME,
                                       strlen((const char *)HOST_NAME),
                                       &g_ulDestinationIP,SL_AF_INET);
    if(lRetVal < 0)
    {
        ASSERT_ON_ERROR(GET_HOST_IP_FAILED);
    }

    // Create a TCP connection to the Web Server
    g_iSockID = CreateConnection(g_ulDestinationIP);

    if(g_iSockID < 0)
    {
        UART_PRINT("Connection to server failed\n\r");
        return SERVER_CONNECTION_FAILED;
    }
    else
    {
        UART_PRINT("Connection to server created successfully\r\n");
    }
    // Download the file, verify the file and replace the exiting file
    lRetVal = GetData();
    if(lRetVal < 0)
    {
        UART_PRINT("Device couldn't download the file from the server\n\r");
    }

    lRetVal = sl_Close(g_iSockID);
    if( 0 > lRetVal )
    {
        UART_PRINT("Failed during closing socket\r\n");
        return lRetVal;
    }
    return SUCCESS;
}
//*****************************************************************************
//
//! Application startup display on UART
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
static void
DisplayBanner(char * AppName)
{
    UART_PRINT("\n\n\n\r");
    UART_PRINT("\t\t *************************************************\n\r");
    UART_PRINT("\t\t      CC3200 %s Application       \n\r", AppName);
    UART_PRINT("\t\t *************************************************\n\r");
    UART_PRINT("\n\n\n\r");
}


//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
static void
BoardInit(void)
{
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
  //
  // Set vector table base
  //
#if defined(ccs) || defined(gcc)
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
    MAP_IntVTableBaseSet((unsigned long)&__vector_table);
#endif
#endif
    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}


int main()
{
    long lRetVal = -1;

    //
    // Board Initialization
    //
    BoardInit();

    //
    // Configure the pinmux settings for the peripherals exercised
    //
    PinMuxConfig();

    //
    // Configuring UART
    //
    InitTerm();

    //
    // Display banner
    //
    DisplayBanner(APP_NAME);

    InitializeAppVariables();

    lRetVal = ServerFileDownload();

    if(lRetVal < 0)
    {
        UART_PRINT("Server file download failed\n\r");
        LOOP_FOREVER();
    }
    else
    {
        UART_PRINT("Downloading File Completed\n\r");
    }
    UART_PRINT("\nThank you\r\n");
    // Stop the CC3200 device
    lRetVal = sl_Stop(SL_STOP_TIMEOUT);
    
    LOOP_FOREVER();
}


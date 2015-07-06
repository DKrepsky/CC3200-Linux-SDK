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
// Application Name     -   DeepSleep Networking
// Application Overview -   The objective of this application is to showcase 
//                          the deepsleep as a power saving tool in a 
//                          networking context (in this case a TCP server).
// Application Details  -
// http://processors.wiki.ti.com/index.php/CC32xx_Deepsleep_Application
// or
// \docs\examples\CC32xx_Deepsleep_Application.pdf
//
//*****************************************************************************


//****************************************************************************
//
//! \addtogroup deepsleep_nw
//! @{
//
//****************************************************************************
#include <stdlib.h>

// Simplelink includes
#include "simplelink.h"

//Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"
#include "timer.h"

//Free_rtos/ti-rtos includes
#include "osi.h"

//Common interface includes
#include "gpio_if.h"
#include "common.h"
#ifndef NOTERM
#include "uart_if.h"
#endif
#include "pinmux.h"
#include "timer_if.h"
#include "nw_if.h"


#define APPLICATION_NAME        "DeepSleep Networking"
#define APPLICATION_VERSION     "1.1.1"

#define APP_TCP_PORT            5001
#define SYS_CLK                 80000000
#define MAX_BUF                 512
#define FOREVER                 1
#define OSI_STACK_SIZE        3000

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************

// Variable used in Timer Interrupt Handler
unsigned short g_usTimerInts;
// AP Security Parameters
SlSecParams_t SecurityParams = {0};


extern void (* const g_pfnVectors[])(void);

//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************


//****************************************************************************
//                      LOCAL FUNCTION PROTOTYPES
//****************************************************************************
int CreateTCPServerSocket(unsigned int uiPortNum);
void TimerPeriodicIntHandler(void);
void LedTimerConfigNStart();
void LedTimerDeinitStop();
static void DisplayBanner(char * AppName);
static void BoardInit(void);
void TCPServerTask(void *pvParameters);


//****************************************************************************
//                      LOCAL FUNCTION DEFINITIONS
//***************************************************************************

//****************************************************************************
//
//! Creates a TCP socket and binds to it
//!
//! \param uiPortNum is the port number to bind to
//! 
//! This function  
//!    1. Creates a TCP socket and binds to it
//!
//! \return Soceket Descriptor, < 1 if error.
//
//****************************************************************************
int CreateTCPServerSocket(unsigned int uiPortNum)
{
    int iSockDecs, lRetVal;
    sockaddr_in sServerAddress;

    //
    // Create a TCP socket
    //
    iSockDecs = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    ASSERT_ON_ERROR(iSockDecs);

    //
    // Bind - Assign a port to the socket
    //
    sServerAddress.sin_family = AF_INET;
    sServerAddress.sin_addr.s_addr = INADDR_ANY;
    sServerAddress.sin_port = htons(uiPortNum);
    lRetVal = bind(iSockDecs,
              (struct sockaddr*)&sServerAddress,
               sizeof(sServerAddress));
    ASSERT_ON_ERROR(lRetVal);

    return iSockDecs;
}

//*****************************************************************************
//
//! Periodic Timer Interrupt Handler
//!
//! \param None
//!
//! \return None
//
//*****************************************************************************
void
TimerPeriodicIntHandler(void)
{
    unsigned long ulInts;
    
    //
    // Clear all pending interrupts from the timer we are
    // currently using.
    //
    ulInts = MAP_TimerIntStatus(TIMERA0_BASE, true);
    MAP_TimerIntClear(TIMERA0_BASE, ulInts);
    
    //
    // Increment our interrupt counter.
    //
    g_usTimerInts++;
    if(!(g_usTimerInts & 0x1))
    {
        //
        // Off Led
        //
        GPIO_IF_LedOff(MCU_RED_LED_GPIO);
    }
    else
    {
        //
        // On Led
        //
        GPIO_IF_LedOn(MCU_RED_LED_GPIO);
    }
}

//****************************************************************************
//
//! Function to configure and start timer to blink the LED while device is
//! trying to connect to an AP
//!
//! \param none
//!
//! return none
//
//****************************************************************************
void LedTimerConfigNStart()
{
  //
  // Configure Timer for blinking the LED for IP acquisition
  //
  Timer_IF_Init(PRCM_TIMERA0,TIMERA0_BASE,TIMER_CFG_PERIODIC,TIMER_A,0);
  Timer_IF_IntSetup(TIMERA0_BASE,TIMER_A,TimerPeriodicIntHandler);
  Timer_IF_Start(TIMERA0_BASE,TIMER_A,100);     // time value is in mSec
}

//****************************************************************************
//
//! Disable the LED blinking Timer as Device is connected to AP
//!
//! \param none
//!
//! return none
//
//****************************************************************************
void LedTimerDeinitStop()
{
  //
  // Disable the LED blinking Timer as Device is connected to AP
  //
  Timer_IF_Stop(TIMERA0_BASE,TIMER_A);
  Timer_IF_DeInit(TIMERA0_BASE,TIMER_A);

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
    Report("\n\n\n\r");
    Report("\t\t *************************************************\n\r");
    Report("\t\t     CC3200 %s Application       \n\r", AppName);
    Report("\t\t *************************************************\n\r");
    Report("\n\n\n\r");
}

//****************************************************************************
//
//! Task function implementing the TCP server and showcasing the  
//! deepsleep functionality
//!
//! \param none
//! 
//! This function  
//!    1. Creates a TCP socket and binds to it
//!    2. Listens on the socket
//!    3. Accepts a client connection
//!    4. Receives a packet on the socket
//!    5. Closes the socket
//!
//! \return None.
//
//****************************************************************************
void TCPServerTask(void *pvParameters)
{
    int iSocketDesc, iClientFD;
    long lRetVal = -1;
    struct sockaddr_in sClientAddr;
    int iRecvLen;
    unsigned short usClientAddrLen = sizeof(sClientAddr);
    unsigned char aucRecvBuffer[MAX_BUF];

    DisplayBanner(APPLICATION_NAME);

    DBG_PRINT("DEEPSLEEP: Test Begin\n\r");

    //
    // GPIO Configuration
    //
    GPIO_IF_LedConfigure(LED1|LED3);

    GPIO_IF_LedOff(MCU_RED_LED_GPIO);
    GPIO_IF_LedOff(MCU_GREEN_LED_GPIO);    

    //
    // Start the driver
    //
    lRetVal = Network_IF_InitDriver(ROLE_STA);
    if(lRetVal < 0)
    {
       UART_PRINT("Failed to start SimpleLink Device\n\r");
       LOOP_FOREVER();
    }    

    GPIO_IF_LedOn(MCU_GREEN_LED_GPIO);

    LedTimerConfigNStart();

    // Initialize AP security params
    SecurityParams.Key = (signed char*)SECURITY_KEY;
    SecurityParams.KeyLen = strlen(SECURITY_KEY);
    SecurityParams.Type = SECURITY_TYPE;

    //
    // Connect to the Access Point
    //
    lRetVal = Network_IF_ConnectAP(SSID_NAME,SecurityParams);
    if(lRetVal < 0)
    {
       Report("Connection to AP failed\n\r");
       GPIO_IF_LedOff(MCU_IP_ALLOC_IND);
       LOOP_FOREVER();
    }

    LedTimerDeinitStop();

    //
    // Switch ON RED LED to indicate that Device acquired an IP
    //
    GPIO_IF_LedOn(MCU_IP_ALLOC_IND);

    //
    // Create and Bind TCP server socket
    //
    iSocketDesc = CreateTCPServerSocket(APP_TCP_PORT);
    if(iSocketDesc < 0)
    {
        DBG_PRINT("DEEPSLEEP: Socket create failed\n");
        goto end;
    }
    DBG_PRINT("DEEPSLEEP: Socket created\n\r");
    DBG_PRINT("DEEPSLEEP: Listening on Socket...\n\r");

    //
    // Start Listening on the socket
    //
    if( listen(iSocketDesc, 5) != 0)
    {
        DBG_PRINT("DEEPSLEEP: Listen failed\n\r");
        goto end;
    }

    while(FOREVER)
    {
        //
        // Accept new client connections (Here just one)
        //
        DBG_PRINT("DEEPSLEEP: Waiting for client.......\n\r");
        iClientFD = accept(iSocketDesc, 
                       (struct sockaddr*)&sClientAddr, 
                       &usClientAddrLen);
        if(iClientFD < 0)
        {
            ERR_PRINT(iClientFD);
            break;
        }

        DBG_PRINT("DEEPSLEEP: Connected to client [0x%x] \n\r", 
                           htonl(sClientAddr.sin_addr.s_addr));

        do
        {
            //
            // Receive on the socket
            //
            iRecvLen = recv(iClientFD,aucRecvBuffer,MAX_BUF,0);

            if(iRecvLen > 0)
            {
                DBG_PRINT("DEEPSLEEP: received %d bytes\n\r", iRecvLen);
                DBG_PRINT("DEEPSLEEP: received message : %s\n\r", aucRecvBuffer);
            }
            else
            {
                ERR_PRINT(iRecvLen);
                break;
            }
        }while(iRecvLen > 0);

        //
        // Close the client descriptor
        //
        close(iClientFD);
    }



end:

    //
    // Close the socket. Commented as not expected to reach here
    //
    close(iSocketDesc);

    //
    // Stop the driver
    //
    lRetVal = Network_IF_DeInitDriver();
    if(lRetVal < 0)
    {
       UART_PRINT("Failed to stop SimpleLink Device\n\r");
       LOOP_FOREVER();
    }

    //
    // Switch Off RED & Green LEDs to indicate that Device is
    // disconnected from AP and Simplelink is shutdown
    //
    GPIO_IF_LedOff(MCU_IP_ALLOC_IND);
    GPIO_IF_LedOff(MCU_GREEN_LED_GPIO);

    DBG_PRINT("DEEPSLEEP: Test Complete\n\r");

    //
    // Loop here
    //
    LOOP_FOREVER();
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
    //
    // Set vector table base
    //
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);

    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}

//****************************************************************************
//
//! Main function
//!
//! \param none
//! 
//! This function  
//!    1. Invokes the SLHost task
//!    2. Invokes the LPDSTCPServerTask
//!
//! \return None.
//
//****************************************************************************
void main()
{
    long lRetVal = -1;

    //
    // Initialize the board
    //
    BoardInit();

    //
    // Configure the pinmux settings for the peripherals exercised
    //
    PinMuxConfig();

#ifndef NOTERM
    //
    // Configuring UART
    //
    InitTerm();
    ClearTerm();
#endif

    //
    // Start the SimpleLink Host
    //
    lRetVal = VStartSimpleLinkSpawnTask(SPAWN_TASK_PRIORITY);
    if(lRetVal < 0)
    {
        ERR_PRINT(lRetVal);
        LOOP_FOREVER();
    }

    //
    // Start the TCPServer task
    //
    lRetVal = osi_TaskCreate(TCPServerTask,
                    (const signed char *)"DeepSleep TCP",
                    OSI_STACK_SIZE, 
                    NULL, 
                    1, 
                    NULL );
    if(lRetVal < 0)
    {
        ERR_PRINT(lRetVal);
        LOOP_FOREVER();
    }

    //
    // Start the task scheduler
    //
    osi_start();
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

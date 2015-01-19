/*
 * Free_RTOS_Hooks.c
 *
 *  Created on: 22/07/2014
 *      Author: David
 */

#include "FreeRTOS.h"
#include "task.h"
#include "dout.h"


//*****************************************************************************
//
//! Application for handling the assertion.
//! \param  none
//!
//! \return none
//!
//!
//*****************************************************************************
void
vAssertCalled( const char *pcFile, unsigned long ulLine )
{
  	while(1)
    {

    }
}

//*****************************************************************************
//
//! Application defined idle task hook
//! \param  none
//!
//! \return none
//!
//!
//*****************************************************************************
void
vApplicationIdleHook( void )
{

}

//*****************************************************************************
//
//! Application provided stack overflow hook function.
//!
//! \param  handle and name of the offending task
//!
//! \return none
//!
//*****************************************************************************
void
vApplicationStackOverflowHook( TaskHandle_t *pxTask, signed portCHAR *pcTaskName )
{
    ( void ) pxTask;
    ( void ) pcTaskName;

    DOUT("ERROR: FreeRTOS Stack Overflow on task %s\n\r", pcTaskName);
    for( ;; );
}

void vApplicationMallocFailedHook()
{
	DOUT("ERROR: FreeRTOS Allocation error.");
    while(1)
  {
    // Infinite loop;
  }
}

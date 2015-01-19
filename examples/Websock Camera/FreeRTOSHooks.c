/*
 * Free_RTOS_Hooks.c
 *
 *  Created on: 22/07/2014
 *      Author: David
 */

#include <stdint.h>
#include <stddef.h>
#include "osi.h"
//*****************************************************************************
//
//! Application for handling the assertion.
//! \param  none
//!
//! \return none
//!
//!
//*****************************************************************************
void vAssertCalled(const char *pcFile, unsigned long ulLine) {
	while (1) {

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
void vApplicationIdleHook(void) {

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
vApplicationStackOverflowHook( OsiTaskHandle *pxTask, signed char *pcTaskName )
{
	( void ) pxTask;
	( void ) pcTaskName;

	for(;; );
}

void vApplicationMallocFailedHook() {
	while (1) {
		// Infinite loop;
	}
}

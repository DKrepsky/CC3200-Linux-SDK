//*****************************************************************************
//
// Application Name     - LP_Button
// Application Overview - The objective of this application is to showcase the 
//                        GPIO Interrupts. Pressing the button SW2 turns the
//						  red led on, pressing SW3 turns it off.
//
//*****************************************************************************

//****************************************************************************
//
//! \addtogroup LP_Button
//! @{
//
//****************************************************************************

// Standard includes
#include <stdio.h>

// Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "interrupt.h"
#include "prcm.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"
#include "gpio.h"

#include "pinmux.h"

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
extern void (* const g_pfnVectors[])(void);

//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************

//*****************************************************************************
//                      LOCAL FUNCTION DEFINITIONS
//*****************************************************************************

//*****************************************************************************
//
//! Handles the GPIO A2 - SW2 - interrupt. Will turn on the red led.
//!
//! \param None
//!
//! This function
//!    1. Turns the red led on.
//!
//! \return None
//
//*****************************************************************************
void GPIOA2IntHandler(void) {
	MAP_GPIOIntClear(GPIOA2_BASE, GPIO_PIN_6);
	MAP_GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_1, GPIO_PIN_1);
}

//*****************************************************************************
//
//! Handles the GPIO A1 - SW3 - interrupt. Will turn off the red led.
//!
//! \param None
//! 
//! This function  
//!    1. Turns the red led off.
//!
//! \return None
//
//*****************************************************************************
void GPIOA1IntHandler(void) {
	MAP_GPIOIntClear(GPIOA1_BASE, GPIO_PIN_5);
	MAP_GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_1, 0);
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
static void BoardInit(void) {

	//
	// Set vector table base
	//
	MAP_IntVTableBaseSet((unsigned long) &g_pfnVectors[0]);

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
//!    1. Configures the GPIOA1 and A2 interrupt.
//!
//! \return None.
//
//****************************************************************************
int main() {
	//
	// Initialize Board configurations
	//
	BoardInit();

	//
	// Power on the corresponding GPIO port B for 9,10,11.
	// Set up the GPIO lines to mode 0 (GPIO)
	//
	PinMuxConfig();

	//
	// Configure the GPIO13 - SW2 interrupt
	//
	MAP_GPIOIntRegister(GPIOA1_BASE, GPIOA1IntHandler);
	MAP_GPIOIntTypeSet(GPIOA1_BASE, GPIO_PIN_5, GPIO_RISING_EDGE);

	//
	// Configure the GPIO22 interrupt
	//
	MAP_GPIOIntRegister(GPIOA2_BASE, GPIOA2IntHandler);
	MAP_GPIOIntTypeSet(GPIOA2_BASE, GPIO_PIN_6, GPIO_RISING_EDGE);

	//
	// Enable GPIO13 Interrupt
	//
	MAP_GPIOIntClear(GPIOA1_BASE, GPIO_PIN_5);
	MAP_IntPendClear(INT_GPIOA1);
	MAP_IntEnable(INT_GPIOA1);
	MAP_GPIOIntEnable(GPIOA1_BASE, GPIO_PIN_5);

	//
	// Enable GPIO22 Interrupt
	//
	MAP_GPIOIntClear(GPIOA2_BASE, GPIO_PIN_6);
	MAP_IntPendClear(INT_GPIOA2);
	MAP_IntEnable(INT_GPIOA2);
	MAP_GPIOIntEnable(GPIOA2_BASE, GPIO_PIN_6);

	//
	// Infinite loop. All processing happens now in the interrupt handler.
	while (1) {

	}

	return 0;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

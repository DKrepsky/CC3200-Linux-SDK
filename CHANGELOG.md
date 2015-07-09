# CHANGES

### 07/2015 - 1.0.2

- Fix utils delay in driver lib.
- Updated README.md.
- Added Service Pack 1.0.0.10.0 to "other" folder.
- Updated USAGE.md.
- Fixed root Makefile.

### 07/2015 - 1.0.1
- Updated SDK to original version 1.1.0.
- Fixed a bug in cc_timer.c (line 690). A memset was used to clear a struct but the size passed was of a pointer.
- Added BACK_UP_ARM_REGISTERS and RESTORE_ARM_REGISTERS macros to GCC. In cc_pm.c.
- Changed asm to __asm. In cc_pm.c, lines 318, 319 and 320.
- Fixed UNUSED macro in cc_types.h to avoid warnings of uninitialized variables.
- Added braces to initializer in dma_hal.c (lines 184-215).
- Added CPUipsr function for gcc in interrupt_hal.c
- Added initial condition to temp variable in cc_uart_isr (uart_hal.c, line 147).
- Fixed missing HttpString.h and HttpConfig in Http web server. 
- Removed interfaces library (the _if.c files must be linked to project now).
- Removed netapps library (each netapp have its own library now).
- Fixed all the examples from the new SDK version (except bootloader and dynamic library).
- Changed directory structure (libraries source are now unde the folder "src" in the same way that they are within TI SDK).
- Updated documentation.
- Updated FreeRTOS to v8.2.1.
- Every project must include a FreeRTOSConfig.h now.

### 03/2015 - 1.0.0
- Removed FreeRTOS and FatFS source code. This must be placed inside the project
from now on.
- libosi doesn't have FreeRTOS included.
- FreeRTOS 8.0.2 in others folder.
- Fixed variable path CC3200SDK to CC3200-Linux-SDK.
- All examples now contains a .elf and a raw .bin file.

### 02/2015
- Fixed FreeRTOSHooks.c and startup.c includes. 

### 01/2015-2
- -O3 is buggy, compiling with -Os now

### 01/2015
- All libs are compiled with -O3 and no -g
- Added makefile to root dir

### 01/2015

- Added LP_Buttom example.
- Added Assembler help do docs.
- Removed application_bootloader from "other" folder.
- Some changes in ld script for better readability.
- Removed DOUT from FreeRTOSHooks.c.
- Created SimplelinkHooks.c.
- Renamed startup_gcc.c to startup.c.
- Included preprocessor test to remove warnings from startup.c.

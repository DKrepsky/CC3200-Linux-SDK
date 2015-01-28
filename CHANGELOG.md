# CHANGES

## 01/28/2015-2
- -O3 is buggy, compiling with -Os now

## 01/28/2015
- All libs are compiled with -O3 and no -g
- Added makefile to root dir

## 01/27/2015

- Added LP_Buttom example.
- Added Assembler help do docs.
- Removed application_bootloader from "other" folder.
- Some changes in ld script for better readability.
- Removed DOUT from FreeRTOSHooks.c.
- Created SimplelinkHooks.c.
- Renamed startup_gcc.c to startup.c.
- Included preprocessor test to remove warnings from startup.c.

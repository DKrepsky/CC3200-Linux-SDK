# CC3200-Linux-SDK

### Overview
This repo contains a reworked SDK for the CC3200 microcontroller, from Texas 
Instruments, to work under linux.
The intention is to provide a way to develop in this platform while TI doesn't
release an official SDK for linux.
Currently, it works with Ubuntu (tested with version 14.10) and Slackware.

The TI SDK version used for this rework is the 1.1.0 and the original can be
found at : http://www.ti.com/tool/cc3200sdk.

For instructions on how to use it, please see USAGE.md file.

### Changes from the original SDK
- The directory structure of the SDK.
- Replaced all the makefiles for the libs (some of them just didn't work).
- Fixed small issues with gcc for the libraries.
- Ported almost all examples to work with eclipse (except dynamic library and the
    application bootloader).
- Added extra documentation (Datasheet and etc).

For a complete list of changes, see CHANGELOG.md.

### Directory structure
The SDK is organized as follow

- ROOT 
    - doc -> Documentation
    - examples -> Contain several examples adapted to work with eclipse and gcc.
    - lib -> Pre-compiled library files.
    - other -> Configuration files and freeRTOS.
    - src -> The source files and make files for all the libraries.
    
### Rebuilding the libs

Open a terminal in the root directory and do a "make". For the nonos versions
use "make target=NONOS" and for the simplelink tiny "make target=TINY".

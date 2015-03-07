# CC3200-Linux-SDK

version 1.0.0

### Overview
This repo contains a reworked SDK for the CC3200 microcontroller, from Texas 
Instruments, to work under linux.
The intention is to provide a way to develop for this platform while TI doesn't
release an official SDK for linux.
Currently, it works with Ubuntu and Slackware (tested with version 14.10).

The TI SDK version used for this rework is the 1.0.0 and the original can be
found at : http://www.ti.com/tool/cc3200sdk.

For instructions on how to use it, please see USAGE.md file.

### Changes from the original SDK
- The directory structure of the SDK.
- Replaced all the makefiles for the libs (some of them just didn't work).
- Fixed small issues with gcc for the libraries.
- Ported almost all examples to work with eclipse (except the OTA-NONOS and the
    application bootloader).
- Added extra documentation (Datasheet and etc).

For a complete list of changes, see CHANGELOG.md.

### Directory structure
The SDK is organized as follow

- ROOT 
    - doc -> Documentation
    - examples -> Contain several examples adapted to work with eclipse and gcc.
    - include -> Directory for the header files (.h).
    - lib -> Pre-compiled library files.
    - other -> Configuration files and freeRTOS.
    - source -> The source files and make files for all the libraries.
    
### Rebuilding the libs

Open a terminal in the root directory and do a "make". For the nonos versions
use "make target=NONOS" and for the simplelink tiny "make target=TINY".

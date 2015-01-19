# CC3200-Linux-SDK

## Overview
This repo contains a reworked SDK for the CC3200 microcontroller, from Texas Instruments, to work under linux.
The intention is to provide a way to develop for this platform while TI doesn't release a oficial SDK for linux.
Currently, it works with Ubuntu (tested with version 14.10 Utopic).

The TI SDK version used for this rework is the 1.0.0 and the original can be found at : http://www.ti.com/tool/cc3200sdk.

For instructions on how to use it, please see USAGE.md file.

## Changes from the original SDK
- The directory structure of the SDK, for easy use.
- Replaced all the makefiles for the libs (some of them just didn't work).
- Fixed small issues with gcc for the librarys.
- Ported almost all examples to work with eclipse (except the OTA-NONOS and the application bootloader).
- Added extra documentation (Datasheet and etc).

For a complete list of changes, see CHANGELOG.md.
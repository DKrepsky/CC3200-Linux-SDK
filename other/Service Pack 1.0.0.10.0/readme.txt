================================================================================
CC31xx/CC32xx ServicePack image  
Version:	1.0.0.10.0
Date:		Mar 12th, 2015
================================================================================

This package include the ServicePack binary image to be programmed into
CC31xx/CC32xx devices. This firmware shall be used with SDK 1.1.0 only.
The SP image is provided in three formats:
1. UNIFLASH Image
2. OTA (Over the Air) Image
3. Header files for Host Programming

1. UNIFLASH Image 
================================================================================
Files:
- servicepack_1.0.0.10.0.bin

This ServicePack image can be used with pre-production silicon as well as with
production silicon.
The list of silicon that are compatible with this ServicePack are:
 - CC3100R1
 - XCC3100HZ
 - XCC3100JR
 - CC3200R1
 - XCC3200HZ
 - XCC3200JR

The ServicePack shall be programmed using Uniflash utility. Uniflash can be
downloaded from <http://www.ti.com/tool/uniflash>.
The ServicePack can be also used with TI Gang Programmer utility.

2. OTA Image
================================================================================
Files:
- ota\ota_1.0.0.10.0.ucf
- ota\ota_1.0.0.10.0.ucf.sign.bin

This ServicePack image can be used with production silicon only.
The list of silicon that are compatible with this ServicePack are:
 - CC3100R1
 - XCC3100JR
 - CC3200R1
 - XCC3200JR
The ServicePack shall be programmed using the OTA Example found in the
CC3100/CC3200 SDK 1.1.0. 

3. Header files for Host Programming (only for CC3100)
================================================================================
Files:
- host_programming\host_programming_1.0.0.10.0.h
- host_programming\host_programming_1.0.0.10.0_signed.h

This ServicePack image can be used with production silicon only.
The list of silicon that are compatible with this ServicePack are:
 - CC3100R1
 - XCC3100JR
The ServicePack shall be programmed using the host_programming example found in 
the host_programming Update package for CC3100 SDK 1.1.0. 

Notes
================================================================================
Upon successful ServicePack programming, user should expect the following
versions (can be applied using sl_DevGet() API, with SL_DEVICE_GENERAL_VERSION
option):

For HZ (pre-production) devices:
----------------------
NWP version: 2.4.7.2
MAC version: 1.3.4.1
PHY version: 1.5.3.34

For JR and R1 (production) devices:
----------------------
NWP version: 2.4.0.2
MAC version: 1.3.0.1
PHY version: 1.0.3.34

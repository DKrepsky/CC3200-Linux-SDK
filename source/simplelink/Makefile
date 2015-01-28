#******************************************************************************
#
# Makefile - Rules for building the Simplelink library.
#
#	v- 1.0.0
#
#*****************************************************************************

# The base directory.
ROOT=../..

# Output directory
OUTDIR=$(ROOT)/lib

# Lib Name
ifeq ("${target}", "NONOS")
	LIBRARY=${OUTDIR}/libsimplelink_nonos.a
else
	ifeq ("${target}", "TINY")
		LIBRARY=${OUTDIR}/libsimplelink_nonos_tiny.a
	else
	LIBRARY=${OUTDIR}/libsimplelink.a
	endif
endif

# Where to find header files
IPATH=-I$(ROOT)/include
IPATH+=-I$(ROOT)/include/inc
IPATH+=-I${ROOT}/include/oslib
IPATH+=-I$(ROOT)/include/driverlib
IPATH+=-I$(ROOT)/include/simplelink
IPATH+=-I$(ROOT)/include/interfaces

# Executables
VPATH=flc:ota

# Tools Setup
CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar

# C Compiler Flags
CFLAGS=-mthumb             \
       -mcpu=cortex-m4     \
       -ffunction-sections \
       -fdata-sections     \
       -MD                 \
       -std=c99            \
       -Wall		   \
       -Dgcc		   \
       -Dcc3200		   \
       -g              \
       -Os 		   \
       $(IPATH)               

CLAGS+=-DTARGET_IS_CC3200

ifeq ("${target}", "NONOS")
	CFLAGS+=-DSL_FULL 
else
	ifeq ("${target}", "TINY")
		CFLAGS+=-DSL_TINY
	else
	CFLAGS+=-DSL_PLATFORM_MULTI_THREADED
	CFLAGS+=-DUSE_FREERTOS
	CFLAGS+=-DSL_FULL 
	endif
endif

# Sources
SOURCES= cc_pal.c device.c driver.c flowcont.c netapp.c netcfg.c nonos.c fs.c socket.c spawn.c wlan.c 

ifneq ("${target}", "TINY")
SOURCES+=CdnClient.c LogClient.c OtaApp.c OtaClient.c OtaHttp.c flc.c
endif

# Objects
OBJECTS= $(SOURCES:.c=.o)

all: $(SOURCES) $(LIBRARY) remobj 

$(LIBRARY): $(OBJECTS)
	@${AR} -cr $@ $(OBJECTS)
	@echo "AR	$@";	


.c.o: 
	@$(CC) $(CFLAGS) -c $< -o $@ 
	@echo "CC	$@";

remobj:
	@rm -rf *.d
	@rm -rf *.o

clean: remobj
	@rm -rf $(LIBRARY)
	@echo "Clear";    


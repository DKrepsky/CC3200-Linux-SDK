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
ifneq "${target}" "NONOS"
	LIBRARY=${OUTDIR}/libsimplelink.a
else
	LIBRARY=${OUTDIR}/libsimplelink_nonos.a
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
       -g 		   \
       -Wall		   \
       -Dgcc		   \
       -Dcc3200		   \
       -O0 		   \
       $(IPATH)               

ifneq "${target}" "NONOS"
CFLAGS+=-DSL_PLATFORM_MULTI_THREADED
CFLAGS+=-DUSE_FREERTOS
endif

CFLAGS+=-DSL_FULL 

# Sources
SOURCES= cc_pal.c device.c driver.c flowcont.c netapp.c netcfg.c nonos.c fs.c socket.c spawn.c wlan.c CdnClient.c LogClient.c OtaApp.c OtaClient.c OtaHttp.c flc.c

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


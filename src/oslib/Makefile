#******************************************************************************
#
# Makefile - Rules for building the Osi library.
#
#	v- 1.0.1
#
#*****************************************************************************

# The base directory.
ROOT=../..

# Output directory
OUTDIR=$(ROOT)/lib

# RTOS DIR
RTOSDIR=$(ROOT)/other/FreeRTOS

# Lib Name
LIBRARY=${OUTDIR}/libosi.a

# Where to find header files
IPATH=-I$(ROOT)/src
IPATH+=-I$(ROOT)/src/inc
IPATH+=-I${ROOT}/src/oslib
IPATH+=-I$(ROOT)/src/driverlib
IPATH+=-I$(ROOT)/src/simplelink
IPATH+=-I$(ROOT)/src/interfaces
IPATH+=-I$(ROOT)/other
IPATH+=-I${RTOSDIR}
IPATH+=-I${RTOSDIR}/Source
IPATH+=-I${RTOSDIR}/Source/include
IPATH+=-I${RTOSDIR}/Source/portable/MemMang
IPATH+=-I${RTOSDIR}/Source/portable/GCC/ARM_CM4

# External source files
VPATH=${RTOSDIR}
VPATH+=:${RTOSDIR}/source
VPATH+=:${RTOSDIR}/source/portable/MemMang
VPATH+=:${RTOSDIR}/source/portable/GCC/ARM_CM4

# Tools Setup
CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar

# C Compiler Flags
CFLAGS=-mthumb              \
       -mcpu=cortex-m4      \
       -ffunction-sections  \
       -fdata-sections      \
       -MD                  \
       -std=c99             \
       -Wall		        \
       -Dgcc		        \
       -Dcc3200		        \
       -Os 		            \
       -g                   \
       $(IPATH)        
       
CFLAGS+=-DTARGET_IS_CC3200       

# Sources
SOURCES= osi_freertos.c

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


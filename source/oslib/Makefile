
#******************************************************************************
#
# Makefile - Rules for building the Osi library.
#
#	v- 1.0.0
#
#*****************************************************************************

# The base directory.
ROOT=../..

# Output directory
OUTDIR=$(ROOT)/lib

# RTOS DIR
RTOSDIR=$(ROOT)/external/FreeRTOS

# Lib Name
LIBRARY=${OUTDIR}/libosi.a

# Where to find header files
IPATH=-I$(ROOT)/include
IPATH+=-I$(ROOT)/include/inc
IPATH+=-I${ROOT}/include/oslib
IPATH+=-I$(ROOT)/include/driverlib
IPATH+=-I$(ROOT)/include/simplelink
IPATH+=-I$(ROOT)/include/interfaces
IPATH+=-I${RTOSDIR}
IPATH+=-I${RTOSDIR}/source
IPATH+=-I${RTOSDIR}/source/include
IPATH+=-I${RTOSDIR}/source/portable/MemMang
IPATH+=-I${RTOSDIR}/source/portable/GCC/ARM_CM4

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
SOURCES= croutine.c list.c queue.c tasks.c port.c timers.c heap_3.c osi_freertos.c

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





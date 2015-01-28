#******************************************************************************
#
# Makefile - Rules for building the Interfaces library.
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
	LIBRARY=${OUTDIR}/libinterfaces.a
else
	LIBRARY=${OUTDIR}/libinterfaces_nonos.a
endif


# Where to find header files
IPATH=-I$(ROOT)/include
IPATH+=-I$(ROOT)/include/inc
IPATH+=-I${ROOT}/include/oslib
IPATH+=-I$(ROOT)/include/driverlib
IPATH+=-I$(ROOT)/include/simplelink
IPATH+=-I$(ROOT)/include/interfaces

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
       -O3 		   \
       $(IPATH)               

ifneq "${target}" "NONOS"
CFLAGS+=-DSL_PLATFORM_MULTI_THREADED
CFLAGS+=-DUSE_FREERTOS
endif

CFLAGS+=-DTARGET_IS_CC3200

# Sources
SOURCES= button_if.c gpio_if.c i2c_if.c network_if.c timer_if.c uart_if.c utils_if.c wdt_if.c udma_if.c

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

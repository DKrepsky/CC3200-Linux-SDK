#******************************************************************************
#
# Makefile - Rules for building the Middleware library.
#
#	v- 1.0.1
#
#*****************************************************************************

# The base directory.
ROOT=../..

# Output directory
OUTDIR=$(ROOT)/lib

# Lib Name
ifneq "${target}" "NONOS"
	LIBRARY=${OUTDIR}/libmiddleware.a
else
	LIBRARY=${OUTDIR}/libmiddleware_nonos.a
endif



# Where to find header files
IPATH+=-I../
IPATH+=-I../inc
IPATH+=-I../driverlib
IPATH+=-I../oslib
IPATH+=-I../simplelink/include
IPATH+=-Idriver
IPATH+=-Idriver/hal
IPATH+=-Iframework/pm
IPATH+=-Iframework/timer
IPATH+=-Isoc


# External source files
VPATH=soc:framework/timer:framework/pm:driver/hal:driver

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
       -DUSE_FREERTOS	    \
       -Os 		            \
       -g                   \
       $(IPATH)               

CFLAGS+=-DTARGET_IS_CC3200

ifneq "${target}" "NONOS"
CFLAGS+=-DSL_PLATFORM_MULTI_THREADED
CFLAGS+=-DUSE_FREERTOS
endif

# Sources
## soc
SOURCES=cc_io_park.c cc_pm_ops.c

## framework
### timer
SOURCES+=cc_timer.c

### pm
SOURCES+=cc_pm.c

## driver
SOURCES+= spi_drv.c uart_drv.c

### hal
SOURCES+= dma_hal.c gpio_hal.c hw_timer32.c interrupt_hal.c rtc_hal.c spi_hal.c uart_hal.c util64.c

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



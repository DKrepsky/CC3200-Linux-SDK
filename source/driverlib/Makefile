#******************************************************************************
#
# Makefile - Rules for building the Driverlib library.
#
#	v- 1.0.0
#
#*****************************************************************************

# The base directory.
ROOT=../..

# Output directory
OUTDIR=$(ROOT)/lib

# Lib Name
LIBRARY=${OUTDIR}/libdriver.a

# Where to find header files
IPATH=-I$(ROOT)/include/driverlib
IPATH+=-I$(ROOT)/include

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
       -O3 		   \
       -Dgcc		   \
       -Dcc3200		   \
       -DTARGET_IS_CC3200 \
       $(IPATH)               

# Sources
SOURCES= adc.c aes.c camera.c cpu.c crc.c des.c flash.c gpio.c hwspinlock.c i2c.c \
	interrupt.c i2s.c pin.c prcm.c sdhost.c shamd5.c spi.c systick.c timer.c \
	uart.c udma.c utils.c wdt.c

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




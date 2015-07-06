#******************************************************************************
#
# Makefile - Rules for building the FLC library.
#
#	v- 1.0.0
#
#*****************************************************************************

# The base directory.
ROOT=../../..

# Output directory
OUTDIR=$(ROOT)/lib

# Lib Name
LIBRARY=${OUTDIR}/libflc.a

# Where to find header files
IPATH=-I$(ROOT)/src/driverlib
IPATH+=-I$(ROOT)/src/simplelink
IPATH+=-I$(ROOT)/src/simplelink/include
IPATH+=-I${ROOT}/src/oslib
IPATH+=-I$(ROOT)/src/inc
IPATH+=-I$(ROOT)/src/simplelink_extlib/include

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

CFLAGS+=-DSL_PLATFORM_MULTI_THREADED
CFLAGS+=-DUSE_FREERTOS
CFLAGS+=-DSL_FULL 


# Sources
SOURCES= flc.c 

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
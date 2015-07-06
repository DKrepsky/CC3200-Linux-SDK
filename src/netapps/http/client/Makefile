#******************************************************************************
#
# Makefile - Rules for building the Http client library.
#
#	v- 1.0.1
#
#*****************************************************************************

# The base directory.
ROOT=../../../..

# Output directory
OUTDIR=$(ROOT)/lib

# Lib Name
LIBRARY=${OUTDIR}/libwebclient.a

# Where to find header files
IPATH+=-I../..
IPATH+=-I$(ROOT)/src/driverlib
IPATH+=-I$(ROOT)/src/simplelink/include

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
       -Os 		            \
       -g                   \
       -Dgcc		        \
       -Dcc3200		        \
       -DTARGET_IS_CC3200   \
       -D__SL__             \
       -DHTTPCli_LIBTYPE_MIN\
       $(IPATH)               

# Sources
SOURCES= httpcli.c httpstr.c ssock.c

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


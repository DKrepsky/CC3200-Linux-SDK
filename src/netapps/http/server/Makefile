#******************************************************************************
#
# Makefile - Rules for building the Http web server library.
#
#	v- 1.0.0
#
#*****************************************************************************

# The base directory.
ROOT=../../../..

# Output directory
OUTDIR=$(ROOT)/lib

# Lib Name
LIBRARY=${OUTDIR}/libwebserver.a

# Where to find header files
IPATH+=-I$(ROOT)/src/inc
IPATH+=-I$(ROOT)/src/driverlib
IPATH+=-I$(ROOT)/src/oslib
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
       -Dgcc		        \
       -DUSE_FREERTOS	    \
       -Os 		            \
       -g                   \
       $(IPATH)               

CFLAGS+=-DTARGET_IS_CC3200
CFLAGS+=-DSL_PLATFORM_MULTI_THREADED
CFLAGS+=-DUSE_FREERTOS

# Sources
SOURCES= base64.c  HttpAuth.c HttpCore.c HttpDebug.c HttpDynamic.c HttpSocket.c HttpStatic.c \
	HttpString.c sha1.c strlib.c WebSockHandler.c

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



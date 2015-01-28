#******************************************************************************
#
# Makefile - Rules for building the Xmpp library.
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
	LIBRARY=${OUTDIR}/libnetapps.a
else
	LIBRARY=${OUTDIR}/libnetapps_nonos.a
endif



# Where to find header files
IPATH=-I$(ROOT)/include
IPATH+=-I$(ROOT)/include/inc
IPATH+=-I${ROOT}/include/oslib
IPATH+=-I$(ROOT)/include/driverlib
IPATH+=-I$(ROOT)/include/interfaces
IPATH+=-I$(ROOT)/include/simplelink
IPATH+=-I$(ROOT)/include/netapps/http
IPATH+=-I$(ROOT)/include/netapps/smtp
IPATH+=-I$(ROOT)/include/netapps/tftp
IPATH+=-I$(ROOT)/include/netapps/xmpp
IPATH+=-I$(ROOT)/include/netapps/pubnub

# External source files
VPATH=http:tftp:smtp:tftp:xmpp:pubnub:.

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
SOURCES= tftp.c tftp6.c base64.c xmpp.c email.c 

ifneq "${target}" "NONOS"
	SOURCES+= HttpAuth.c HttpCore.c HttpDebug.c HttpDynamic.c HttpSocket.c HttpStatic.c \
	HttpString.c sha1.c strlib.c WebSockHandler.c
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


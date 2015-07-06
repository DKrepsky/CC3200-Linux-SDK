#******************************************************************************
#
# Makefile - Rules for building the MQTT library.
#
#	v- 1.0.0
#
#*****************************************************************************

# The base directory.
ROOT=../../..

# Output directory
OUTDIR=$(ROOT)/lib

# Lib Name
LIBRARY=${OUTDIR}/libmqtt.a

# Where to find header files
IPATH=-I$(ROOT)/src/driverlib
IPATH+=-I$(ROOT)/src/simplelink
IPATH+=-I$(ROOT)/src/simplelink/include
IPATH+=-I${ROOT}/src/oslib
IPATH+=-I$(ROOT)/src/inc
IPATH+=-I$(ROOT)/src/netapps/mqtt
IPATH+=-I$(ROOT)/src/netapps/mqtt/client
IPATH+=-I$(ROOT)/src/netapps/mqtt/common
IPATH+=-I$(ROOT)/src/netapps/mqtt/include
IPATH+=-I$(ROOT)/src/netapps/mqtt/platform
IPATH+=-I$(ROOT)/src/netapps/mqtt/server
IPATH+=-I$(ROOT)/src/netapps/mqtt/sl

# External source files
VPATH=client:common:include:platform:server:sl

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
       -DUSE_FREERTOS		\
       -DSL_PLATFORM_MULTI_THREADED\
       $(IPATH)               

# Sources
SOURCES= cc31xx_sl_net.c cc3200_platform.c client_mgmt.c mqtt_client.c mqtt_common.c server_core.c server_pkts.c server_plug.c server_util.c sl_mqtt_client.c sl_mqtt_server.c 

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


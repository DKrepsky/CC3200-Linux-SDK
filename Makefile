DRIVERLIB = src/driverlib
SIMPLELINK = src/simplelink
OSLIB = src/oslib
MIDDLEWARE = src/middleware
WEBCLIENT = src/netapps/http/client
WEBSERVER = src/netapps/http/server
JSON = src/netapps/json
MQTT = src/netapps/mqtt
SMTP = src/netapps/smtp/client
TFTP = src/netapps/tftp/client
XMPP = src/netapps/xmpp/client

ifeq ("${target}", "NONOS")
	SDK_TARGETS = $(SIMPLELINK) $(MIDDLEWARE) 
else
	ifeq ("${target}", "TINY")
		SDK_TARGETS = $(SIMPLELINK)
	else
	SDK_TARGETS = $(DRIVERLIB) $(SIMPLELINK) $(OSLIB) $(MIDDLEWARE) $(WEBCLIENT) $(WEBSERVER) $(JSON) $(MQTT) $(SMTP) $(TFTP) $(XMPP)
	endif
endif

.PHONY: all clean $(SDK_TARGETS)

all: $(SDK_TARGETS)

$(SDK_TARGETS):
	cd $@ && $(MAKE)

clean: 
	rm -rf lib/*
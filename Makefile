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


SDK_TARGETS = $(DRIVERLIB) $(SIMPLELINK) $(OSLIB) $(MIDDLEWARE) $(WEBCLIENT) $(WEBSERVER) $(JSON) $(MQTT) $(SMTP) $(TFTP) $(XMPP)
SDK_TARGETS_NONOS = $(SIMPLELINK) $(MIDDLEWARE) 
SDK_TARGETS_TINY = $(SIMPLELINK)


.PHONY: all
all: os nonos tiny

os: $(SDK_TARGETS)

nonos: $(SDK_TARGETS_NONOS)

tiny: $(SDK_TARGETS_TINY)

.PHONY: $(SDK_TARGETS)
$(SDK_TARGETS):
	@$(MAKE) -C $@

$(SDK_TARGETS_NONOS):
	@$(MAKE) -C $@ target=NONOS

$(SDK_TARGETS_TINY):
	@$(MAKE) -C $@ target=TINY;

clean: 
	rm -rf lib/*
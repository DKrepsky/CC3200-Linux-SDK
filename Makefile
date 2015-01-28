DRIVERLIB = source/driverlib
SIMPLELINK = source/simplelink
OSLIB = source/oslib
MIDDLEWARE = source/middleware
INTERFACES = source/interfaces
NETAPP = source/netapps

ifeq ("${target}", "NONOS")
	SDK_TARGETS = $(SIMPLELINK) $(MIDDLEWARE) $(INTERFACES) $(NETAPP)
else
	ifeq ("${target}", "TINY")
		SDK_TARGETS = $(SIMPLELINK)
	else
		SDK_TARGETS = $(DRIVERLIB) $(SIMPLELINK) $(OSLIB) $(MIDDLEWARE) $(INTERFACES) $(NETAPP)
	endif
endif

.PHONY: all $(SDK_TARGETS)
all: $(SDK_TARGETS)

clean: 
	rm -rf lib/*

$(SDK_TARGETS):
	@$(MAKE) -C $@;

$(SDK_TARGETS_NONOS):
	@$(MAKE) -C $@ target=NONOS;

$(SDK_TARGETS_TINY):
	@$(MAKE) -C $@ target=TINY;

install: netserver-install

netserver-install: netdatabase-install
	cd server/source && $(MAKE) && $(MAKE) install && $(MAKE) clean
	
netdatabase-install: netgraph-install
	cd database/source && $(MAKE) && $(MAKE) install && $(MAKE) clean
	
netgraph-install:
	cd graph/source && $(MAKE) && $(MAKE) install && $(MAKE) clean

	
test: netgraph-test netdatabase-test netserver-test

netserver-test:
	cd server/tests && $(MAKE)
	
netdatabase-test:
	cd database/tests && $(MAKE)
	
netgraph-test:
	cd graph/tests && $(MAKE)
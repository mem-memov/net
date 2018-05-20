netserver: netdatabase
	cd server/source && $(MAKE) && $(MAKE) install
	
netdatabase: netgraph
	cd database/source && $(MAKE) && $(MAKE) install
	
netgraph:
	cd graph/source && $(MAKE) && $(MAKE) install


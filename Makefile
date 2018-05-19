server: database
	cd server/source && $(MAKE) && $(MAKE) install
	
database:
	cd database/source && $(MAKE) && $(MAKE) install


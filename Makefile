server: database
	$(MAKE) -C server/source

database:
	cd database/source && $(MAKE) && $(MAKE) install


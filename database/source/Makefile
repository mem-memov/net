netdatabase: main.o Collection.o Collections.o Database.o
	gcc  main.o Collection.o Collections.o Database.o -lnetgraph -o netdatabase

Collection.o: Collection.c Collection.h
	gcc -Wall -c Collection.c
	
Collections.o: Collections.c Collections.h
	gcc -Wall -c Collections.c
	
Database.o: Database.c Database.h
	gcc -Wall -c Database.c
	
clean:
	rm --force *.o netdatabase libnetdatabase.a
	
install:
	install netdatabase /usr/local/bin/netdatabase && rm --force main.o && ar -rcs libnetdatabase.a *.o && cp libnetdatabase.a /usr/local/lib/libnetdatabase.a && cp Database.h /usr/local/include/netdatabase.h

uninstall:
	rm --force netdatabase /usr/local/bin/netdatabase /usr/local/lib/libnetdatabase.a /usr/local/include/netdatabase.h
netdatabase: main.o Database.o
	gcc  main.o Database.o -lnetgraph -o netdatabase

Database.o: Database.c Database.h
	gcc -Wall -c Database.c
	
install:
	install netdatabase /usr/local/bin/netdatabase && rm --force main.o && ar -rcs libnetdatabase.a *.o && cp libnetdatabase.a /usr/local/lib/libnetdatabase.a && cp Database.h /usr/local/include/netdatabase.h

uninstall:
	rm --force netdatabase /usr/local/bin/netdatabase /usr/local/lib/libnetdatabase.a /usr/local/include/netdatabase.h
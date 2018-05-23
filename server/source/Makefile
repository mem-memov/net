netserver: main.o Application.o Connection.o Error.o Listener.o Parameter.o Request.o Response.o Server.o Signal.o Thread.o 
	gcc main.o Application.o Connection.o Error.o Listener.o Parameter.o Request.o Response.o Server.o Signal.o Thread.o -pthread -lnetdatabase -o netserver

main.o: main.c Server.h
	gcc -c main.c

Application.o: Application.c Application.h Request.h Response.h Error.h
	gcc -c Application.c

Connection.o: Connection.c Connection.h Request.h Response.h Error.h
	gcc -c Connection.c

Error.o: Error.c Error.h
	gcc -c Error.c

Listener.o: Listener.c Listener.h Connection.h Request.h Response.h Error.h
	gcc -c Listener.c

Parameter.o: Parameter.c Parameter.h
	gcc -c Parameter.c

Request.o: Request.c Request.h
	gcc -c Request.c

Response.o: Response.c Response.h
	gcc -c Response.c

Server.o: Server.c Server.h Listener.h Connection.h Request.h Response.h Application.h
	gcc -c Server.c

Signal.o: Signal.c Signal.h Server.h
	gcc -c Signal.c

Thread.o: Thread.c Thread.h
	gcc -c Thread.c

clean:
	rm --force *.o netserver

install:
	install netserver /usr/local/bin/netserver

uninstall:
	rm /usr/local/bin/netserver

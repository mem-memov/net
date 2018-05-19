net-server: main.o Application.o Connection.o Error.o Listener.o Request.o Response.o Server.o Signal.o
	gcc main.o Application.o Connection.o Error.o Listener.o Request.o Response.o Server.o Signal.o -o net-server

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

Request.o: Request.c Request.h
	gcc -c Request.c

Response.o: Response.c Response.h
	gcc -c Response.c

Server.o: Server.c Server.h Listener.h Connection.h Request.h Response.h Application.h
	gcc -c Server.c

Signal.o: Signal.c Signal.h Server.h
	gcc -c Signal.c

clean:
	rm --force *.o net-server

install:
	install net-server /usr/local/bin/net-server

uninstall:
	rm /usr/local/bin/net-server

#include "Server.h"
#include "Listener.h"
#include "Connection.h"
#include "Request.h"
#include "Response.h"
#include "Error.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

#include "Parameter.h"
#include "Thread.h"
#include "Threads.h"

struct Server {
    int port;
    int connectionLimit;
    int bufferLength;
    struct Listener * listener;
    struct Application * application;
	
	struct Threads * threads;
};

struct Server * Server_construct(int port, int connectionLimit, int bufferLength, struct Application * application)
{
	struct Server * this = malloc(sizeof(struct Server));

	this->port = port;
	this->connectionLimit = connectionLimit;
	this->bufferLength = bufferLength;
	this->listener = NULL;
    this->application = application;
	
	this->threads = Threads_construct();
	

	return this;
}

void Server_destruct(struct Server * this)
{
    if (NULL != this->listener)
    {
        Listener_destruct(this->listener);
    }

    free(this);
	this = NULL;
}

void * testing(void * arg)
{
	printf("oooooo\n");
	
	struct Parameter * parameter = (struct Parameter *)arg;
	struct Connection * connection = Parameter_getConnection(parameter);
	struct Thread * thread = Parameter_getThread(parameter);

	while (1) {
		Connection_receive(connection);

		if (1 == Connection_isIdle(connection))
		{
			continue;
		}

		if (1 == Connection_mustClose(connection))
		{
			Connection_close(connection);
			break;
		}

		//Application_execute(this->application, Connection_request(connection), Connection_response(connection));
		Connection_send(connection);
	}
	
	Thread_stop(thread);
}

void Server_start(struct Server * this)
{
    this->listener = Listener_construct(this->port, this->connectionLimit);

    Listener_open(this->listener);
    Listener_bind(this->listener);
    Listener_listen(this->listener);
	
	struct Thread * thread = Threads_make(this->threads);
	int oooo = 1;
	
	struct Thread * threads[10];
	int index = 0;
	
	while (1) {
		struct Connection * connection = Listener_accept(this->listener, this->bufferLength);
		index++;
		threads[index] = Threads_make(this->threads);
		struct Parameter * parameter = Parameter_construct(connection, threads[index]);
		Thread_start(threads[index], testing, (void *)parameter);
		printf("%d\n", index);
	}
}

void Server_stop(struct Server * this)
{
    if (NULL != this->listener)
    {
        Listener_close(this->listener);
    }
}





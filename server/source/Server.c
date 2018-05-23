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

struct Server {
    int port;
    int connectionLimit;
    int bufferLength;
	int threadNumber;
    struct Listener * listener;
    struct Application * application;
};

struct Server * Server_construct(
	int port, 
	int connectionLimit, 
	int bufferLength, 
	int threadNumber,
	struct Application * application
) {
	struct Server * this = malloc(sizeof(struct Server));

	this->port = port;
	this->connectionLimit = connectionLimit;
	this->bufferLength = bufferLength;
	this->threadNumber = threadNumber;
	this->listener = NULL;
    this->application = application;
	
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

static void * runInThread(void * arg)
{
	struct Parameter * parameter = (struct Parameter *)arg;
	struct Listener * listener = Parameter_getListener(parameter);
	struct Application * application = Parameter_getApplication(parameter);
	int bufferLength = Parameter_getBufferLength(parameter);
	
	while (1) {
		struct Connection * connection = Listener_accept(listener, bufferLength);

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

			Application_execute(application, Connection_request(connection), Connection_response(connection));
			Connection_send(connection);
		}
	}
}

void Server_start(struct Server * this)
{
    this->listener = Listener_construct(this->port, this->connectionLimit);

    Listener_open(this->listener);
    Listener_bind(this->listener);
    Listener_listen(this->listener);
	
	struct Thread ** threads = malloc(sizeof(struct Thread *) * this->threadNumber);

	int i;
	for ( i = 0; i < this->threadNumber; i++ ) {
		threads[i] = Thread_construct();
		struct Parameter * parameter = Parameter_construct(this->listener, this->bufferLength, this->application);
		Thread_start(threads[i], runInThread, (void *)parameter);
	}
	
	for ( i = 0; i < this->threadNumber; i++ ) {
		Thread_stop(threads[i]);
	}
}

void Server_stop(struct Server * this)
{
    if (NULL != this->listener)
    {
        Listener_close(this->listener);
    }
}
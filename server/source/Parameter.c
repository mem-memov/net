#include "Parameter.h"
#include <stdlib.h>

struct Parameter
{
	struct Connection * connection;
	struct Thread * thread;
	struct Application * application;
};

struct Parameter * Parameter_construct(struct Connection * connection, struct Thread * thread, struct Application * application)
{
	struct Parameter * this = malloc(sizeof(struct Parameter));
	
	this->connection = connection;
	this->thread = thread;
	this->application = application;

	return this;
}

void Parameter_destruct(struct Parameter * this)
{
	free(this);
	this = NULL;
}

struct Connection * Parameter_getConnection(struct Parameter * this)
{
	return this->connection;
}

struct Thread * Parameter_getThread(struct Parameter * this)
{
	return this->thread;
}

struct Application * Parameter_getApplication(struct Parameter * this)
{
	return this->application;
}
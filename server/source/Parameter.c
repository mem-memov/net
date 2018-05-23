#include "Parameter.h"
#include <stdlib.h>

struct Parameter
{
	struct Connection * connection;
	struct Thread * thread;
};

struct Parameter * Parameter_construct(struct Connection * connection, struct Thread * thread)
{
	struct Parameter * this = malloc(sizeof(struct Parameter));
	
	this->connection = connection;
	this->thread = thread;

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
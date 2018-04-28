#include "../../source/LinkError.h"
#include <stdlib.h>

struct LinkError {
	size_t origin;
	size_t destination;
	char * method;
};

struct LinkError * LinkError_mock()
{
	struct LinkError * this = malloc(sizeof(struct LinkError));
	
	this->origin = 55555;
	this->destination = 55555;
	this->method = "method not specified";

	return this;
}

void LinkError_destruct(struct LinkError * this)
{
	free(this);
	this = NULL;
}

void LinkError_forbidSelfPointingNodes(struct LinkError * this, size_t origin, size_t destination)
{
	this->method = "LinkError_forbidSelfPointingNodes";
	this->origin = origin;
	this->destination = destination;
}

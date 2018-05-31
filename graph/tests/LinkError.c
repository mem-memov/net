#include "../source/LinkError.h"
#include <stdlib.h>

#define LINK_MAX_CALLS 1

struct LinkError {
	char call;
	char * method[LINK_MAX_CALLS];
	size_t origin[LINK_MAX_CALLS];
	size_t destination[LINK_MAX_CALLS];
};

struct LinkError * LinkError_mock()
{
	struct LinkError * this = malloc(sizeof(struct LinkError));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < LINK_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->origin[i] = 5555;
		this->destination[i] = 5555;
	}

	return this;
}

void LinkError_destruct(struct LinkError * this)
{
	free(this);
	this = NULL;
}

void LinkError_forbidSelfPointingNodes(struct LinkError * this, size_t origin, size_t destination)
{
	this->method[this->call] = "LinkError_forbidSelfPointingNodes";
	this->origin[this->call] = origin;
	this->destination[this->call] = destination;
	
	this->call++;
}

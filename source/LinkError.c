#include "LinkError.h"
#include <stdlib.h>

struct LinkError {

};

struct LinkError * LinkError_construct()
{
	struct LinkError * this = malloc(sizeof(struct LinkError));

	return this;
}

void LinkError_destruct(struct LinkError * this)
{
	free(this);
	this = NULL;
}

void LinkError_forbidSelfPointingNodes(struct LinkError * this, size_t origin, size_t destination)
{
	if (origin == destination) {
		exit(1);
	}
}
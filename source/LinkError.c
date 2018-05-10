#include "LinkError.h"
#include <stdlib.h>
#include "Error.h"

struct LinkError {
	struct Error * error;
};

struct LinkError * LinkError_construct(struct Error * error)
{
	struct LinkError * this = malloc(sizeof(struct LinkError));
	
	this->error = error;

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
		Error_terminate(this->error);
	}
}
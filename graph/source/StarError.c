#include "StarError.h"

struct StarError
{
	struct Error * error;
};

struct StarError * StarError_construct(struct Error * error)
{
	struct StarError * this = malloc(sizeof(struct StarError));
	
	this->error = error;

	return this;
}

void StarError_destruct(struct StarError * this)
{
	free(this);
	this = NULL;
}
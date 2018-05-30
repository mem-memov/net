#include "Stars.h"
#include <stdlib.h>

struct Stars
{
	struct Links * links;
	struct StarError * starError;
};

struct Stars * Stars_construct(struct Links * links, struct StarError * starError)
{
	struct Stars * this = malloc(sizeof(struct Stars));
	
	this->links = links;
	this->starError = starError;

	return this;
}

void Stars_destruct(struct Stars * this)
{
	free(this);
	this = NULL;
}

struct Star * Stars_make(struct Stars * this)
{
	return Star_construct(
		Links_make(this->links),
		Links_make(this->links),
		this->starError
	);
}
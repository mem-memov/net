#include "Places.h"
#include <stdlib.h>
#include "Place.h"

struct Places
{
	unsigned char length;
	unsigned char * bytes;
};

struct Places * Places_construct(unsigned char length, unsigned char * bytes)
{
	struct Places * this = malloc(sizeof(struct Places));
	
	this->length = length;
	this->bytes = bytes;
	
	return this;
}

void Places_destruct(struct Places * this)
{
	free(this);
	this = NULL;
}

struct Place * Places_make(struct Places * this)
{
	return Place_construct(this->length, this->bytes);
}

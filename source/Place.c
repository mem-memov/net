#include "Place.h"
#include <stdlib.h>

struct Place
{
	unsigned char length;
};

struct Place * Place_construct(unsigned char length)
{
	struct Place * this = malloc(sizeof(struct Place));
	
	this->length = length;
	
	return this;
}

void Place_destruct(struct Place * this)
{
	free(this);
	this = NULL;
}

size_t Place_getValue()
{
	
}
#include "Place.h"
#include <stdlib.h>

struct Place
{
	unsigned char length;
	unsigned char * places;
};

struct Place * Place_construct(unsigned char length, unsigned char * places)
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

size_t Place_getValue(struct Place * this, size_t position)
{
	size_t value = 0;
	unsigned char index;
	
	for (index = 0; index < this->length; index++) {
		value += this->places[position * this->length + index];
	}
	
	return value;
}

void Place_setValue(struct Place * this, size_t position, size_t value)
{
	
}
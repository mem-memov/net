#include "Exports.h"
#include <stdlib.h>

struct Exports
{
	unsigned char * bytes;
};

struct Exports * Exports_construct(unsigned char * bytes)
{
	struct Exports * this = malloc(sizeof(struct Exports));
	
	this->bytes = bytes;

	return this;
}

void Exports_destruct(struct Exports * this)
{
	free(this);
	this = NULL;
}

struct Export * Exports_make(struct Exports * this, size_t size)
{
	return Export_construct(this->bytes, size);
}
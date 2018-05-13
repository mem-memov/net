#include "Export.h"
#include <stdlib.h>

struct Export
{
	unsigned char * bytes;
	size_t size;
};

struct Export * Export_construct(unsigned char * bytes, size_t size)
{
	struct Export * this = malloc(sizeof(struct Export));
	
	this->bytes = bytes;
	this->size = size;

	return this;
}

void Export_destruct(struct Export * this)
{
	free(this);
	this = NULL;
}

void Export_write(struct Export * this, FILE * file)
{
	size_t byteCount = fwrite(this->bytes, sizeof(unsigned char), this->size, file);
	
	if ( byteCount != this->size ) {
		exit(1);
	}
}
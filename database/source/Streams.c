#include "Streams.h"
#include <stdlib.h>

struct Streams
{
	unsigned char * bytes;
};

struct Streams * Streams_construct(unsigned char * bytes)
{
	struct Streams * this = malloc(sizeof(struct Streams));
	
	this->bytes = bytes;

	return this;
}

void Streams_destruct(struct Streams * this)
{
	free(this);
	this = NULL;
}

struct Stream * Streams_make(struct Streams * this, FILE * file)
{
	return Stream_construct(this->bytes, file);
}
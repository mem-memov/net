#include "Export.h"
#include <stdlib.h>

struct Export
{
	struct Streams * streams;
	size_t size;
};

struct Export * Export_construct(struct Streams * streams, size_t size)
{
	struct Export * this = malloc(sizeof(struct Export));
	
	this->streams = streams;
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
	struct Stream * stream = Streams_make(this->streams, file);
	
	Stream_write(stream, this->size);
	
	Stream_destruct(stream);
}
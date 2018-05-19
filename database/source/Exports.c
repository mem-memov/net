#include "Exports.h"
#include <stdlib.h>

struct Exports
{
	struct Streams * streams;
};

struct Exports * Exports_construct(struct Streams * streams)
{
	struct Exports * this = malloc(sizeof(struct Exports));
	
	this->streams = streams;

	return this;
}

void Exports_destruct(struct Exports * this)
{
	free(this);
	this = NULL;
}

struct Export * Exports_make(struct Exports * this, size_t size)
{
	return Export_construct(this->streams, size);
}
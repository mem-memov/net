#include "Imports.h"
#include <stdlib.h>

struct Imports
{
	struct Streams * streams;
};

struct Imports * Imports_construct(struct Streams * streams)
{
	struct Imports * this = malloc(sizeof(struct Imports));
	
	this->streams = streams;

	return this;
}

void Imports_destruct(struct Imports * this)
{
	free(this);
	this = NULL;
}

struct Import * Imports_make(struct Imports * this)
{
	return Import_construct(this->streams);
}
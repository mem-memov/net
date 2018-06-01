#include "Imports.h"
#include <stdlib.h>

struct Imports
{
	struct Streams * streams;
	size_t entrySize;
	size_t placeSize;
	struct Boat * boat;
};

struct Imports * Imports_construct(struct Streams * streams, size_t entrySize, size_t placeSize, struct Boat * boat)
{
	struct Imports * this = malloc(sizeof(struct Imports));
	
	this->streams = streams;
	this->entrySize = entrySize;
	this->placeSize = placeSize;
	this->boat = boat;

	return this;
}

void Imports_destruct(struct Imports * this)
{
	free(this);
	this = NULL;
}

struct Import * Imports_make(struct Imports * this)
{
	return Import_construct(this->streams, this->entrySize, this->placeSize, this->boat);
}
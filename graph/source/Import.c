#include "Import.h"
#include <stdlib.h>

struct Import
{
	struct Streams * streams;
	size_t entrySize;
	size_t placeSize;
	struct Boat * boat;
};

struct Import * Import_construct(struct Streams * streams, size_t entrySize, size_t placeSize, struct Boat * boat)
{
	struct Import * this = malloc(sizeof(struct Import));
	
	this->streams = streams;
	this->entrySize = entrySize;
	this->placeSize = placeSize;
	this->boat = boat;

	return this;
}

void Import_destruct(struct Import * this)
{
	free(this);
	this = NULL;
}

void Import_read(struct Import * this, FILE * file)
{
	struct Stream * stream = Streams_make(this->streams, file);
	
	Stream_read(stream, 0, this->entrySize * this->placeSize);

	Boat_read(this->boat);

	Boat_import(this->boat, stream);
	
	Stream_destruct(stream);
}
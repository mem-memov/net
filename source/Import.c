#include "Import.h"
#include <stdlib.h>

struct Import
{
	struct Streams * streams;
};

struct Import * Import_construct(struct Streams * streams)
{
	struct Import * this = malloc(sizeof(struct Import));
	
	this->streams = streams;

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
	
//	Stream_read(stream, this->entrySize);
	
	Stream_destruct(stream);
	
	
//	size_t headPlaces = fread(this->bytes, sizeof(unsigned char), this->entrySize, file);
//	
//	if (headPlaces != this->entrySize) {
//		exit(1);
//	}
//	
//	Net_read(this->net);
//	
//	if (Net_isSpaceCut(this->net)) {
//		exit(1);
//	}
//	
//	Net_import(this->net, file);
}
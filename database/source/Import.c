#include "Import.h"
#include <stdlib.h>

struct Import
{
	struct Streams * streams;
	size_t entrySize;
	size_t placeSize;
	struct Net * net;
};

struct Import * Import_construct(struct Streams * streams, size_t entrySize, size_t placeSize, struct Net * net)
{
	struct Import * this = malloc(sizeof(struct Import));
	
	this->streams = streams;
	this->entrySize = entrySize;
	this->placeSize = placeSize;
	this->net = net;

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

	Net_read(this->net);

	Net_import(this->net, stream);
	
	Stream_destruct(stream);
}
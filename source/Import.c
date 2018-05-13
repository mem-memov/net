#include "Import.h"
#include <stdlib.h>

struct Import
{
	unsigned char * bytes;
};

struct Import * Import_construct(unsigned char * bytes)
{
	struct Import * this = malloc(sizeof(struct Import));
	
	this->bytes = bytes;

	return this;
}

void Import_destruct(struct Import * this)
{
	free(this);
	this = NULL;
}

void Import_read(struct Import * this, FILE * file)
{
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
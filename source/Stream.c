#include "Stream.h"
#include <stdlib.h>

struct Stream
{
	unsigned char * bytes;
	FILE * file;
};

struct Stream * Stream_construct(unsigned char * bytes, FILE * file)
{
	struct Stream * this = malloc(sizeof(struct Stream));
	
	this->bytes = bytes;
	this->file = file;

	return this;
}

void Stream_destruct(struct Stream * this)
{
	free(this);
	this = NULL;
}

void Stream_read(struct Stream * this, size_t offset, size_t length)
{
	size_t byteCount = fread(this->bytes + offset, sizeof(unsigned char), length, this->file);
	
	if ( byteCount != length ) {
		exit(1);
	}
}

void Stream_write(struct Stream * this, size_t length)
{
	size_t byteCount = fwrite(this->bytes, sizeof(unsigned char), length, this->file);
	
	if ( byteCount != length ) {
		exit(1);
	}
}
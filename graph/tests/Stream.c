#include "../source/Stream.h"

#define STREAM_MAX_CALLS 1

struct Stream
{
	char call;
	char * method[STREAM_MAX_CALLS];
	size_t offset[STREAM_MAX_CALLS];
	size_t length[STREAM_MAX_CALLS];
};

struct Stream * Stream_mock()
{
	struct Stream * this = malloc(sizeof(struct Stream));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < STREAM_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->offset[i] = 55555;
		this->length[i] = 55555;
	}

	return this;
}

void Stream_destruct(struct Stream * this)
{
	free(this);
	this = NULL;
}

void Stream_read(struct Stream * this, size_t offset, size_t length)
{
	this->method[this->call] = "Stream_read";
	this->offset[this->call] = offset;
	this->length[this->call] = length;
	
	this->call++;
}

void Stream_write(struct Stream * this, size_t length)
{
	this->method[this->call] = "Stream_write";
	this->length[this->call] = length;
	
	this->call++;
}
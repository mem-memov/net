#ifndef STREAM_H
#define STREAM_H

#include <stdio.h>

struct Stream;

struct Stream * Stream_construct(unsigned char * bytes, FILE * file);

void Stream_destruct(struct Stream * this);

size_t Stream_read(struct Stream * this, size_t offset, size_t length);

size_t Stream_write(struct Stream * this, size_t length);

#endif
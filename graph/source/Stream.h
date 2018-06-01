#ifndef STREAM_H
#define STREAM_H

#include <stdio.h>
#include <stdlib.h>

struct Stream;

struct Stream * Stream_construct(unsigned char * bytes, FILE * file);

void Stream_destruct(struct Stream * this);

void Stream_read(struct Stream * this, size_t offset, size_t length);

void Stream_write(struct Stream * this, size_t length);

#endif
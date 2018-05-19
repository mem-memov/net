#ifndef STREAMS_H
#define STREAMS_H

#include <stdio.h>
#include "Stream.h"

struct Streams;

struct Streams * Streams_construct();

void Streams_destruct(struct Streams * this);

struct Stream * Streams_make(struct Streams * this, FILE * file);

#endif
#ifndef DUMP_H
#define DUMP_H

#include <stdlib.h>
#include <stdio.h>

struct Dump;

struct Dump * Dump_construct(size_t * places, FILE * file);

void Dump_destruct(struct Dump * this);

#endif


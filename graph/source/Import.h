#ifndef IMPORT_H
#define IMPORT_H

#include <stdio.h>
#include "Boat.h"
#include "Streams.h"

struct Import;

struct Import * Import_construct(struct Streams * streams, size_t entrySize, size_t placeSize, struct Boat * boat);

void Import_destruct(struct Import * this);

void Import_read(struct Import * this, FILE * file);

#endif
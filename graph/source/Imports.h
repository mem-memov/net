#ifndef IMPORTS_H
#define IMPORTS_H

#include "Import.h"
#include "Boat.h"
#include "Streams.h"

struct Imports;

struct Imports * Imports_construct(struct Streams * streams, size_t entrySize, size_t placeSize, struct Boat * boat);

void Imports_destruct(struct Imports * this);

struct Import * Imports_make(struct Imports * this);

#endif
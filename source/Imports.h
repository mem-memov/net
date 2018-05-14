#ifndef IMPORTS_H
#define IMPORTS_H

#include "Import.h"
#include "Net.h"
#include "Streams.h"

struct Imports;

struct Imports * Imports_construct(struct Streams * streams, size_t entrySize, size_t placeSize, struct Net * net);

void Imports_destruct(struct Imports * this);

struct Import * Imports_make(struct Imports * this);

#endif
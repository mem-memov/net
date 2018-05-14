#ifndef IMPORTS_H
#define IMPORTS_H

#include "Import.h"
#include "Streams.h"

struct Imports;

struct Imports * Imports_construct(struct Streams * streams);

void Imports_destruct(struct Imports * this);

struct Import * Imports_make(struct Imports * this);

#endif
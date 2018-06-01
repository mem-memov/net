#ifndef KNITTER_H
#define KNITTER_H

#include <stdlib.h>
#include "KnitterError.h"
#include "Mesh.h"
#include "Place.h"
#include "Space.h"
#include "Stream.h"

struct Knitter;

struct Knitter * Knitter_construct(
	size_t entrySize, 
	struct Place * placeSize,
	struct Place * nextPlace,
	struct Place * gapPlace,
	struct Mesh * mesh,
	struct Space * space,
	struct KnitterError * error
);

void Knitter_destruct(struct Knitter * this);

void Knitter_create(struct Knitter * this, size_t placeSize);

void Knitter_read(struct Knitter * this);

char Knitter_hasCreatedEntry(struct Knitter * this, size_t place);

char Knitter_canCreateEntry(struct Knitter * this);

size_t Knitter_createEntry(struct Knitter * this);

void Knitter_deleteEntry(struct Knitter * this, size_t place);

size_t Knitter_calculateSize(struct Knitter * this);

void Knitter_import(struct Knitter * this, struct Stream * stream, size_t graphSize);

#endif

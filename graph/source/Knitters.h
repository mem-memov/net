#ifndef KNITTERS_H
#define KNITTERS_H

#include <stdlib.h>
#include "Knitter.h"
#include "KnitterError.h"
#include "Meshes.h"
#include "Places.h"
#include "Spaces.h"

struct Knitters;

struct Knitters * Knitters_construct(
	struct Meshes * meshes, 
	struct Places * places, 
	struct Spaces * spaces,
	struct KnitterError * knitterError
);

void Knitters_destruct(struct Knitters * this);

struct Knitter * Knitters_make(struct Knitters * this, size_t entrySize);

#endif

#ifndef NETS_H
#define NETS_H

#include "Counts.h"
#include "Exports.h"
#include "Meshes.h"
#include "Net.h"
#include "Places.h"

struct Nets;

struct Nets * Nets_construct(
	struct Places * places, 
	struct Counts * counts, 
	struct Meshes * meshes, 
	struct Exports * exports
);

void Nets_destruct(struct Nets * this);

struct Net * Nets_make(struct Nets * this, size_t spaceSize, size_t entrySize);

#endif


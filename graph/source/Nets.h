#ifndef NETS_H
#define NETS_H

#include <stdlib.h>
#include "Net.h"
#include "NetError.h"
#include "Meshes.h"
#include "Places.h"
#include "Spaces.h"

struct Nets;

struct Nets * Nets_construct(
	struct Meshes * meshes, 
	struct Places * places, 
	struct Spaces * spaces,
	struct NetError * netError
);

void Nets_destruct(struct Nets * this);

struct Net * Nets_make(struct Nets * this, size_t entrySize);

#endif

#ifndef BOATS_H
#define BOATS_H

#include <stdlib.h>
#include "Counts.h"
#include "Exports.h"
#include "Nets.h"
#include "Boat.h"
#include "BoatError.h"
#include "Places.h"

struct Boats;

struct Boats * Boats_construct(
	struct Places * places, 
	struct Counts * counts, 
        struct Nets * nets,
	struct Exports * exports,
        struct BoatError * boatError
);

void Boats_destruct(struct Boats * this);

struct Boat * Boats_make(struct Boats * this, size_t graphSize, size_t entrySize, size_t placeSize);

#endif


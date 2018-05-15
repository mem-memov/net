#ifndef GAP_H
#define GAP_H

#include <stdlib.h>
#include "GapError.h"
#include "Place.h"

struct Gap;

struct Gap * Gap_construct(
	struct Place * zero,
	struct Place * count,
	struct Place * next,
	struct Place * three,
	struct Place * four,
	struct Place * five, 
	struct GapError * error
);

void Gap_destruct(struct Gap * this);

void Gap_create(struct Gap * this, size_t place, size_t nextGapPlace, size_t count);

void Gap_read(struct Gap * this, size_t place);

void Gap_delete(struct Gap * this);

size_t Gap_increment(struct Gap * this);

size_t Gap_getNext(struct Gap * this);

#endif
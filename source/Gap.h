#ifndef GAP_H
#define GAP_H

#include <stdlib.h>
#include "GapError.h"

struct Gap;

struct Gap * Gap_construct(size_t place, struct Gap * next, struct GapError * error);

void Gap_destruct(struct Gap * this);

size_t Gap_getPlace(struct Gap * this);

struct Gap * Gap_getNext(struct Gap * this);

#endif
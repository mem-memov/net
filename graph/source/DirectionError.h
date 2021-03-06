#ifndef DIRECTIONERROR_H
#define DIRECTIONERROR_H

#include <stdlib.h>
#include "Error.h"

struct DirectionError;

struct DirectionError * DirectionError_construct(struct Error * error);

void DirectionError_destruct(struct DirectionError * this);

void DirectionError_forbidZeroPlaceForPrevious(struct DirectionError * this, size_t previous);

void DirectionError_forbidZeroAndEqualtyForPreviousAndNext(struct DirectionError * this, size_t * previous, size_t * next);

#endif


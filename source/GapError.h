#ifndef GAPERROR_H
#define GAPERROR_H

#include <stdlib.h>
#include "Error.h"

struct GapError;

struct GapError * GapError_construct(struct Error * error);

void GapError_destruct(struct GapError * this);

void GapError_zeroPlaceIsReservedForInvalidGap(struct GapError * this, size_t place);

void GapError_placeCanBeReadOnlyOnce(struct GapError * this, size_t place);

#endif
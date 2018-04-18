#ifndef GAPERROR_H
#define GAPERROR_H

#include <stdlib.h>

struct GapError;

struct GapError * GapError_construct();

void GapError_destruct(struct GapError * this);

void GapError_zeroPlaceIsReservedForInvalidGap(struct GapError * this, size_t place);

void GapError_placeCanBeReadOnlyOnce(struct GapError * this, size_t place);

#endif
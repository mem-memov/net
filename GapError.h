#ifndef GAPERROR_H
#define GAPERROR_H

#include <stdlib.h>

struct GapError;

struct GapError * GapError_construct();

void GapError_destruct(struct GapError * this);

void GapError_zeroPlaceIsReservedForInvalidGap(size_t place);

void GapError_placeCanBeReadOnlyOnce(size_t place);

#endif
#ifndef GAPERROR_H
#define GAPERROR_H

#include <stdlib.h>
#include "Error.h"

struct GapError;

struct GapError * GapError_construct(struct Error * error);

void GapError_destruct(struct GapError * this);

#endif
#ifndef COUNTERROR_H
#define COUNTERROR_H

#include <stdlib.h>
#include "Error.h"

struct CountError;

struct CountError * CountError_construct(struct Error * error);

void CountError_destruct(struct CountError * this);

void CountError_forbidNegativeValueWhenDecrementing(struct CountError * this, size_t value);

void CountError_forbidOverflowWhenIncrementing(struct CountError * this, size_t value);

#endif
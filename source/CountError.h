#ifndef COUNTERROR_H
#define COUNTERROR_H

#include <stdlib.h>

struct CountError;

struct CountError * CountError_construct();

void CountError_destruct(struct CountError * this);

void CountError_forbidNegativeValueWhenDecrementing(struct CountError * this, size_t value);

#endif
#ifndef STARERROR_H
#define STARERROR_H

#include <stdlib.h>
#include "Error.h"

struct StarError;

struct StarError * StarError_construct(struct Error * error);

void StarError_destruct(struct StarError * this);

#endif

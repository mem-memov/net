#ifndef KNITTERERROR_H
#define KNITTERERROR_H

#include <stdlib.h>
#include "Error.h"

struct KnitterError;

struct KnitterError * KnitterError_construct(struct Error * error);

void KnitterError_destruct(struct KnitterError * this);

void KnitterError_requireFittingInSize(struct KnitterError * this, size_t nextPlace, size_t graphSize);

#endif

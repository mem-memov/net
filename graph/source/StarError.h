#ifndef STARERROR_H
#define STARERROR_H

#include <stdlib.h>
#include "Error.h"

struct StarError;

struct StarError * StarError_construct(struct Error * error);

void StarError_destruct(struct StarError * this);

void StarError_forbidShortDestinationList(struct StarError * this, size_t outgoingLink, size_t index, size_t maxIndex);

void StarError_forbidLongDestinationList(struct StarError * this, size_t outgoingLink);

void StarError_forbidShortOriginList(struct StarError * this, size_t incomingLink, size_t index, size_t maxIndex);

void StarError_forbidLongOriginList(struct StarError * this, size_t incomingLink);

#endif

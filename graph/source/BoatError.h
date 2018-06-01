#ifndef BOATERROR_H
#define BOATERROR_H

#include <stdlib.h>
#include "Error.h"

struct BoatError;

struct BoatError * BoatError_construct(struct Error * error);

void BoatError_destruct(struct BoatError * this);

void BoatError_requireOboatoVerifyCorrectPlaceSize(struct BoatError * this, size_t one);

void BoatError_requireFittingInSize(struct BoatError * this, size_t nextPlace, size_t graphSize);

void BoatError_requireFreeSpaceAvailable(struct BoatError * this, char isAvailable);

#endif

#ifndef NETERROR_H
#define NETERROR_H

#include <stdlib.h>
#include "Error.h"

struct NetError;

struct NetError * NetError_construct(struct Error * error);

void NetError_destruct(struct NetError * this);

void NetError_requireOneToVerifyCorrectPlaceSize(struct NetError * this, size_t one);

void NetError_requireFittingInSize(struct NetError * this, size_t nextPlace, size_t graphSize);

void NetError_requireFreeSpaceAvailable(struct NetError * this, char isAvailable);

#endif

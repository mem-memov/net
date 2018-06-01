#ifndef SPACE_H
#define SPACE_H

#include <stdlib.h>

struct Space;

struct Space * Space_construct(size_t graphSize);

void Space_destruct(struct Space * this);

char Space_canTakeAnotherEntry(struct Space * this, size_t nextPlace, size_t gapPlace);

#endif

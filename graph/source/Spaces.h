#ifndef SPACES_H
#define SPACES_H

#include <stdlib.h>
#include "Space.h"

struct Spaces;

struct Spaces * Spaces_construct(size_t graphSize);

void Spaces_destruct(struct Spaces * this);

struct Space * Spaces_make(struct Spaces * this);

#endif

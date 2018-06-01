#ifndef SPACES_H
#define SPACES_H

#include "Space.h"

struct Spaces;

struct Spaces * Spaces_construct();

void Spaces_destruct(struct Spaces * this);

struct Space * Spaces_make(struct Spaces * this);

#endif

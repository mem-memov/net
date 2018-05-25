#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include "Collection.h"

struct Collections;

struct Collections * Collections_construct();

void Collections_destruct(struct Collections * this);

struct Collection * Collections_make(struct Collections * this, size_t length);

#endif
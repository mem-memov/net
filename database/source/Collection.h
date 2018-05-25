#ifndef COLLECTION_H
#define COLLECTION_H

#include <stdlib.h>

struct Collection;

struct Collection * Collection_construct(size_t length);

void Collection_destruct(struct Collection * this);

void Collection_addNode(struct Collection * this, size_t node);

#endif
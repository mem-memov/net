#ifndef COLLECTION_H
#define COLLECTION_H

#include "Entry.h"

struct Collection;

struct Collection * Collection_construct(size_t length);

void Collection_destruct(struct Collection * this);

void Collection_addEntry(struct Collection * this, struct Entry * entry);

#endif
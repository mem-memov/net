#ifndef COLLECTION_H
#define COLLECTION_H

struct Collection;

struct Collection * Collection_construct();

void Collection_destruct(struct Collection * this);

#endif
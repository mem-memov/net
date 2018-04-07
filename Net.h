#ifndef NET_H
#define NET_H

#include "Node.h"
#include "Space.h"

struct Net {
	struct Space * space;
};

struct Net * Net_construct(struct Space * space);

void Net_destruct(struct Net * this);

char Net_canAddNode(struct Net * this);

struct Node * Net_addNode(struct Net * this);

struct Node * Net_getNode(struct Net * this, unsigned int nodePlace);

#endif
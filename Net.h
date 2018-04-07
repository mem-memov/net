#ifndef NET_H
#define NET_H

#include "Node.h"
#include "Space.h"

struct Net {
	struct Space * space;
};

struct Net * Net_construct(struct Space * space);

void Net_destruct(struct Net * this);

struct Node * addNode(struct Net * this);

struct Node * getNode(struct Net * this, int nodePlace);

#endif
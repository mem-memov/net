#ifndef NET_H
#define NET_H

#include "Node.h"

struct Net {
	unsigned int size;
	unsigned int increment;
	struct Node ** nodes;
	unsigned int offset;
};

struct Net * Net_construct(unsigned int size, unsigned int increment);

void Net_destruct(struct Net * this);

char Net_canAddNode(struct Net * this);

struct Node * Net_addNode(struct Net * this);

struct Node * Net_getNode(struct Net * this, unsigned int nodePlace);

#endif
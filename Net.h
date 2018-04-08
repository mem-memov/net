#ifndef NET_H
#define NET_H

#include "Node.h"

struct Net {
	unsigned int size;
	unsigned int offset;
	struct Node ** nodes;
	struct Error * error;
};

struct Net * Net_construct(unsigned int size, struct Error * error);

void Net_destruct(struct Net * this);

char Net_canAddNode(struct Net * this);

struct Node * Net_addNode(struct Net * this);

struct Node * Net_getNode(struct Net * this, unsigned int nodePlace);

#endif
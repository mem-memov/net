#ifndef LINK_H
#define LINK_H

#include "Node.h"

struct Link {
	struct Node * node;
	struct Link * previous;
};

struct Link * Link_construct(
	struct Node * node,
	struct Link * previous
);

void Link_destruct(struct Link * this);

unsigned int Link_getNodePlace(struct Link * this);

void Link_appendNode(struct Link * this, unsigned int nodePlace);

#endif
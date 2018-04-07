#ifndef NODE_H
#define NODE_H

#include "Link.h"

struct Node {
	unsigned int place;
	struct Link * tail;
};

struct Node * Node_construct(unsigned int place);

void Node_destruct(struct Node * node);

unsigned int Node_getPlace(struct Node * this);

void Node_connect(struct Node * this, struct Node * destinationNode);

#endif
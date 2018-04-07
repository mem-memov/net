#ifndef NODE_H
#define NODE_H

#include "Link.h"

struct Node {
	struct Link * head;
};

struct Node * Node_construct(struct Link * head);

void Node_destruct(struct Node * node);

unsigned int Node_getPlace(struct Node * this);

void Node_connect(struct Node * this, struct Node * destinationNode);

#endif
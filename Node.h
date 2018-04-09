#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include "Link.h"

struct Node {
	unsigned int place;
	struct Link * tail;
};

struct Node * Node_construct(unsigned int place);

void Node_destruct(struct Node * node);

unsigned int Node_getPlace(struct Node * this);

void Node_connect(struct Node * this, struct Node * destinationNode);

unsigned int Node_count(struct Node * this);

void Node_export(struct Node * this, FILE * file);

#endif
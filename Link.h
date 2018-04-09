#ifndef LINK_H
#define LINK_H

#include <stdio.h>
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

unsigned int Link_getplace(struct Link * this);

char Link_isConnected(struct Link * this, struct Node * node);

void Link_export(struct Link * this, FILE * file);

#endif
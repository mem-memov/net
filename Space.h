#ifndef SPACE_H
#define SPACE_H

#include <stdio.h>
#include "Net.h"

struct Space {
	size_t spaceSize;
	size_t entrySize;
	size_t placeSize;
	size_t * places;
	struct Net * net;
	struct Gap * gap;
	struct Node * node;
	struct Link * link;
};

struct Space * Space_construct(size_t size);

void Space_destruct(struct Space * this);

char Space_hasFreePlace(struct Space * this);

size_t Space_addNode(struct Space * this);

void Space_removeNode(struct Space * this, size_t place);

void Space_connectNodes(struct Space * this, size_t origin, size_t destination);

void Space_disconnectNodes(struct Space * this, size_t origin, size_t destination);

size_t Space_getNode(struct Space * this, size_t next, size_t * place);

char Space_isNode(struct Space * this, size_t place);

void Space_export(struct Space * this, FILE * file);

void Space_import(struct Space * this, FILE * file);

#endif
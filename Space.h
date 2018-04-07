#ifndef SPACE_H
#define SPACE_H

#include "Link.h"

struct Space {
	int size;
	int * memory;
	int * next;
};

struct Space * Space_construct(int size);

void Space_destruct(struct Space * this);

struct Link * Space_addHeadLink(
	struct Space * this
);

struct Link * Space_addTailLink(
	struct Space * this, 
	int nodePlace
);

struct Link * Space_getLink(
	struct Space * this, 
	int linkPlace
);

#endif
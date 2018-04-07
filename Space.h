#ifndef SPACE_H
#define SPACE_H

#include "Link.h"

struct Space {
	unsigned int maxLinkNumber;
	unsigned int linkSize;
	unsigned int spaceSize;
	unsigned int nextPlace;
	unsigned int * firstMemoryLocation;
	unsigned int * nextMemoryLocation;
};

struct Space * Space_construct(unsigned int maxLinkNumber);

void Space_destruct(struct Space * this);

char Space_hasPlaceForLinks(
	struct Space * this, 
	unsigned int linkNumber
);

struct Link * Space_addHeadLink(
	struct Space * this
);

struct Link * Space_addTailLink(
	struct Space * this, 
	unsigned int nodePlace
);

struct Link * Space_getLink(
	struct Space * this, 
	unsigned int linkPlace
);

#endif
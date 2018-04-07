#include "Space.h"
#include <stdlib.h>
#include "Link.h"

struct Space * Space_construct(unsigned int maxLinkNumber)
{
	struct Space * this = malloc(sizeof(struct Space));
	
	this->maxLinkNumber = maxLinkNumber;
	this->linkSize = 2;
	this->spaceSize = (this->maxLinkNumber * this->linkSize);
	this->nextPlace = 1;
	
	this->firstMemoryLocation = malloc(sizeof(unsigned int) * this->spaceSize);
	this->nextMemoryLocation = this->firstMemoryLocation;

	return this;
}

void Space_destruct(struct Space * this)
{
	free(this->firstMemoryLocation);
	free(this);
}

char Space_hasPlaceForLinks(
	struct Space * this, 
	unsigned int linkNumber
) {
	unsigned int requestedSize = linkNumber * this->linkSize;
	
	if ((this->nextPlace - 1 + requestedSize) <= this->maxLinkNumber) {
		return 1;
	} else {
		return 0;
	}
}


struct Link * Space_addHeadLink(
	struct Space * this
) {
	// check next is odd
	
	if ( ! Space_hasPlaceForLinks(this, 1)) {
		exit(1);
	}
	
	unsigned int nodePlace = this->nextPlace;

	* (this->nextMemoryLocation) = nodePlace;
	this->nextMemoryLocation++;
	this->nextPlace++;
	
	* (this->nextMemoryLocation) = 0;
	this->nextMemoryLocation++;
	this->nextPlace++;
	
	return Link_construct(nodePlace, 0);
}

struct Link * Space_addTailLink(
	struct Space * this, 
	unsigned int nodePlace
) {
	if ( ! Space_hasPlaceForLinks(this, 1)) {
		exit(1);
	}

	* (this->nextMemoryLocation) = nodePlace;
	this->nextMemoryLocation++;
	this->nextPlace++;
	
	* (this->nextMemoryLocation) = 0;
	this->nextMemoryLocation++;
	this->nextPlace++;
	
	return Link_construct(nodePlace, 0);
}

struct Link * Space_getLink(
	struct Space * this, 
	unsigned int linkPlace
) {
	unsigned int nodePlace = * (this->firstMemoryLocation + (linkPlace - 1) * this->linkSize);
	unsigned int nextLinkPlace = * (this->firstMemoryLocation + linkPlace * this->linkSize);

	return Link_construct(nodePlace, nextLinkPlace);
}
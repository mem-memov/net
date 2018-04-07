#include "Space.h"
#include <stdlib.h>
#include "Link.h"

struct Space * Space_construct(int size)
{
	struct Space * this = malloc(sizeof(struct Space));
	
	this->size = size;
	this->memory = malloc(sizeof(int) * size);
	this->next = this->memory;

	return this;
}

void Space_destruct(struct Space * this)
{
	free(this->memory);
	free(this);
}

struct Link * Space_addHeadLink(
	struct Space * this
) {
	// check next is odd
	
	int nodePlace = this->next - this->memory + 1;
	* (this->next) = nodePlace;
	this->next++;
	* (this->next) = 0;
	this->next++;
	
	return Link_construct(nodePlace, 0);
}

struct Link * Space_addTailLink(
	struct Space * this, 
	int nodePlace
) {
	* (this->next) = nodePlace;
	this->next++;
	* (this->next) = 0;
	this->next++;
	
	return Link_construct(nodePlace, 0);
}

struct Link * Space_getLink(
	struct Space * this, 
	int linkPlace
) {
	int nodePlace = * (this->memory + linkPlace - 1);
	int nextLinkPlace = * (this->memory + linkPlace);
	
	return Link_construct(nodePlace, nextLinkPlace);
}
#include "Link.h"
#include <stdlib.h>

struct Link * Link_construct(
	unsigned int nodePlace,
	unsigned int nextLinkPlace
) {
	struct Link * this = malloc(sizeof(struct Link));

	this->nodePlace = nodePlace;
	this->nextLinkPlace = nextLinkPlace;
	
	return this;
}

void Link_destruct(struct Link * this)
{
	free(this);
}

unsigned int Link_getNodePlace(struct Link * this)
{
	return this->nodePlace;
}

void Link_appendNode(struct Link * this, unsigned int nodePlace)
{
	if (0 == this->nextLinkPlace) {
		this->nextLinkPlace = nodePlace;
	} else {
		Link_appendNode(this->nextLinkPlace, nodePlace);
	}
}
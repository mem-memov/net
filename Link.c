#include "Link.h"
#include <stdlib.h>

struct Link * Link_construct(
	int nodePlace,
	int nextLinkPlace
) {
	struct Link * this = malloc(sizeof(struct Link));

	this->nextLinkPlace = nodePlace;
	this->nextLinkPlace = nextLinkPlace;
	
	return this;
}

void Link_destruct(struct Link * this)
{
	free(this);
}


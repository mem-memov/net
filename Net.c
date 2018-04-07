#include "Net.h"
#include <stdlib.h>
#include "Node.h"
#include "Space.h"

struct Net * Net_construct(struct Space * space)
{
	struct Net * this = malloc(sizeof(struct Net));
	
	this->space = space;

	return this;
}

void Net_destruct(struct Net * this)
{
	Space_destruct(this->space);
	
	free(this);
}

struct Node * addNode(struct Net * this)
{
	return Node_construct(
		Space_addHeadLink(this->space)
	);
}

struct Node * getNode(struct Net * this, int nodePlace)
{
	return Node_construct(
		Space_getLink(this->space, nodePlace)
	);
}
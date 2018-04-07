#include "Net.h"
#include <stdlib.h>
#include "Node.h"

struct Net * Net_construct(unsigned int size)
{
	struct Net * this = malloc(sizeof(struct Net));
	
	this->size = size;
	
	this->nodes = malloc(sizeof(unsigned int) * this->size);
	this->offset = 0;

	return this;
}

void Net_destruct(struct Net * this)
{
	free(this->nodes);
	
	free(this);
}

char Net_canAddNode(struct Net * this)
{
	if (this->offset >= this->size) {
		return 0;
	} else {
		return 1;
	}
}

struct Node * Net_addNode(struct Net * this)
{
	struct Node * node = Node_construct(this->offset + 1);
	
	* (this->nodes + this->offset) = node;
	
	this->offset++;
	
	return node;
}

struct Node * Net_getNode(struct Net * this, unsigned int nodePlace)
{
	return this->nodes[nodePlace - 1];
}
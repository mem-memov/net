#include "Net.h"
#include <stdlib.h>
#include "Error.h"
#include "Node.h"

struct Net * Net_construct(unsigned int size, struct Error * error)
{
	struct Net * this = malloc(sizeof(struct Net));
	
	this->size = size;
	this->offset = 0;
	this->nodes = (struct Node **)malloc(sizeof(unsigned int) * this->size);
	this->error = error;

	return this;
}

void Net_destruct(struct Net * this)
{
	free(this->nodes);
	
	free(this);
}

char Net_canAddNode(struct Net * this)
{
	if (this->offset < this->size) {
		return 1;
	}
	
	return 0;
}

struct Node * Net_addNode(struct Net * this)
{
	Error_netHasNoSpaceLeft(Net_canAddNode(this));
	
	struct Node * node = Node_construct(this->offset + 1);
	
	* (this->nodes + this->offset) = node;
	
	this->offset++;
	
	return node;
}

char Net_hasNode(struct Net * this, unsigned int place)
{
	if (this->offset < place) {
		return 0;
	}
	
	return 1;
}

struct Node * Net_getNode(struct Net * this, unsigned int place)
{
	Error_netHasNoSuchNode(Net_hasNode(this, place), place);
	
	return this->nodes[place - 1];
}
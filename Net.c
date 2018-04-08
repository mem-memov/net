#include "Net.h"
#include <stdlib.h>
#include "Node.h"

struct Net * Net_construct(unsigned int size, unsigned int increment)
{
	struct Net * this = malloc(sizeof(struct Net));
	
	this->size = size;
	this->increment = increment;
	
	this->nodes = (struct Node **)malloc(sizeof(unsigned int) * this->size);
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
		
		unsigned int newSize = this->size + this->increment;
		struct Node ** newNodes = (struct Node **)realloc(this->nodes, newSize);
		
		if (NULL == newNodes) {
			return 0;
		}

		this->nodes = newNodes;
		this->size = newSize;
		
		if (this->offset >= this->size) {
			return 0;
		}
	}
	
	return 1;
}

struct Node * Net_addNode(struct Net * this)
{
	if ( ! Net_canAddNode(this)) {
		exit(1);
	}
	
	struct Node * node = Node_construct(this->offset + 1);
	
	* (this->nodes + this->offset) = node;
	
	this->offset++;
	
	return node;
}

struct Node * Net_getNode(struct Net * this, unsigned int nodePlace)
{
	return this->nodes[nodePlace - 1];
}
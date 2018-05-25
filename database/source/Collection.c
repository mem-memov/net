#include "Collection.h"

struct Collection
{
	size_t * nodes;
	size_t length;
	char isFull;
	size_t index;
};

struct Collection * Collection_construct(size_t length)
{
	struct Collection * this = malloc(sizeof(struct Collection));
	
	this->nodes = malloc(sizeof(size_t) * length);
	this->length = length;
	this->isFull = 0;
	this->index = 0;
	
	size_t index;
	for ( index = 0; index < length; index++ ) {
		this->nodes[index] = 0;
	}

	return this;
}

void Collection_destruct(struct Collection * this)
{
	free(this->nodes);
	free(this);
	this = NULL;
}

void Collection_addNode(struct Collection * this, size_t node)
{
	if (this->isFull) {
		exit(1);
	}
	
	this->nodes[this->index] = node;
	
	if ( this->index == this->length ) {
		this->isFull = 1;
	}
	
	this->index++;
}
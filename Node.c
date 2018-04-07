#include "Node.h"
#include <stdlib.h>
#include "Link.h"

struct Node * Node_construct(unsigned int place)
{
	struct Node * this = malloc(sizeof(struct Node));
	
	this->place = place;
	this->tail = NULL;

	return this;
}

void Node_destruct(struct Node * this)
{
	Link_destruct(this->tail);
	
	free(this);
}

unsigned int Node_getPlace(struct Node * this)
{
	return this->place;
}

void Node_connect(struct Node * this, struct Node * destinationNode)
{
	if (NULL == this->tail) {
		this->tail = Link_construct(destinationNode, NULL);
	} else {
		this->tail = Link_construct(destinationNode, this->tail);
	}
}


#include "Node.h"
#include <stdlib.h>
#include "Link.h"

struct Node * Node_construct(struct Link * head)
{
	struct Node * this = malloc(sizeof(struct Node));
	
	this->head = head;

	return this;
}

void Node_destruct(struct Node * this)
{
	Link_destruct(this->head);
	
	free(this);
}

unsigned int Node_getPlace(struct Node * this)
{
	return Link_getNodePlace(this->head);
}

void Node_connect(struct Node * this, struct Node * destinationNode)
{
	Link_appendNode(this->head, Node_getPlace(destinationNode));
}


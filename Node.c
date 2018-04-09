#include "Node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
		if (! Link_isConnected(this->tail, destinationNode)) {
			this->tail = Link_construct(destinationNode, this->tail);
		}
	}
}

unsigned int Node_count(struct Node * this)
{
	unsigned int count = 0;
	
	if (NULL != this->tail) {
		Link_count(this->tail, &count);
	}
	
	return count;
}

void Node_export(struct Node * this, FILE * file)
{
	fprintf(file, "%u\n", this->place);
	fprintf(file, "%u\n", Node_count(this));
	
	if (NULL != this->tail) {
		Link_export(this->tail, file);
	}
}

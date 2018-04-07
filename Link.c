#include "Link.h"
#include <stdlib.h>
#include "Node.h"

struct Link * Link_construct(
	struct Node * node,
	struct Link * previous
) {
	struct Link * this = malloc(sizeof(struct Link));

	this->node = node;
	this->previous = previous;
	
	return this;
}

void Link_destruct(struct Link * this)
{
	Node_destruct(this->node);
	
	if (NULL != this->previous) {
		Link_destruct(this->previous);
	}
	
	free(this);
}

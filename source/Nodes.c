#include "Nodes.h"
#include <stdlib.h>

struct Nodes
{
	struct Places * places;
	struct Links * links;
	struct NodeError * nodeError;
};

struct Nodes * Nodes_construct(struct Places * places, struct Links * links, struct NodeError * nodeError)
{
	struct Nodes * this = malloc(sizeof(struct Nodes));
	
	this->places = places;
	this->links = links;
	this->nodeError = nodeError;
	
	return this;
}

void Nodes_destruct(struct Nodes * this)
{
	free(this);
	this = NULL;
}

struct Node * Nodes_make(struct Nodes * this)
{
	return Node_construct(
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Links_make(this->links),
		this->nodeError
	);
}

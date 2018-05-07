#include "Nodes.h"
#include <stdlib.h>
#include "Links.h"
#include "NodeError.h"
#include "Places.h"

struct Nodes
{
	struct Places * places;
	struct Links * links;
	struct NodeError * nodeError;
};

struct Nodes * Nodes_construct(Places * places, struct Links * links, struct NodeError * nodeError)
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
		Places_make(),
		Places_make(),
		Places_make(),
		Places_make(),
		Places_make(),
		Places_make(),
		Links_make(),
		this->nodeError
	);
}

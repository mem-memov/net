#include "Nodes.h"
#include <stdlib.h>

struct Nodes
{
	struct Places * places;
	struct Counts * counts;
	struct Stars * stars;
	struct NodeError * nodeError;
};

struct Nodes * Nodes_construct(
	struct Places * places, 
	struct Counts * counts, 
	struct Stars * stars, 
	struct NodeError * nodeError
) {
	struct Nodes * this = malloc(sizeof(struct Nodes));
	
	this->places = places;
	this->counts = counts;
	this->stars = stars;
	this->nodeError = nodeError;
	
	return this;
}

void Nodes_destruct(struct Nodes * this)
{
	NodeError_destruct(this->nodeError);
	
	free(this);
	this = NULL;
}

struct Node * Nodes_make(struct Nodes * this)
{
	return Node_construct(
		Places_make(this->places),
		Places_make(this->places),
		Counts_make(this->counts),
		Counts_make(this->counts),
		Places_make(this->places),
		Places_make(this->places),
		Stars_make(this->stars),
		this->nodeError
	);
}

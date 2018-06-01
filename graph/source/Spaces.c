#include "Spaces.h"

struct Spaces
{
	size_t graphSize;
};

struct Spaces * Spaces_construct(size_t graphSize)
{
	struct Spaces * this = malloc(sizeof(struct Spaces));
	
	this->graphSize = graphSize;

	return this;
}

void Spaces_destruct(struct Spaces * this)
{
	free(this);
	this = NULL;
}

struct Space * Spaces_make(struct Spaces * this)
{
	return Space_construct(this->graphSize);
}
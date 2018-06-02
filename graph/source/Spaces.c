#include "Spaces.h"

struct Spaces
{
	size_t graphSize;
	size_t entrySize;
	size_t placeSize;
};

struct Spaces * Spaces_construct(size_t graphSize, size_t entrySize, size_t placeSize)
{
	struct Spaces * this = malloc(sizeof(struct Spaces));
	
	this->graphSize = graphSize;
	this->entrySize = entrySize;
	this->placeSize = placeSize;

	return this;
}

void Spaces_destruct(struct Spaces * this)
{
	free(this);
	this = NULL;
}

struct Space * Spaces_make(struct Spaces * this)
{
	return Space_construct(this->graphSize, this->entrySize, this->placeSize);
}
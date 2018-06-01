#include "Space.h"

struct Space
{
	size_t graphSize;
};

struct Space * Space_construct(size_t graphSize)
{
	struct Space * this = malloc(sizeof(struct Space));
	
	this->graphSize = graphSize;

	return this;
}

void Space_destruct(struct Space * this)
{
	free(this);
	this = NULL;
}

char Space_canTakeAnotherEntry(struct Space * this, size_t nextPlace, size_t gapPlace)
{
	if ( nextPlace < this->graphSize ) {
		return 1;
	}
	
	if ( 0 != gapPlace ) {
		return 1;
	}
	
	return 0;
}
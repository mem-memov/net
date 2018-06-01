#include "../source/Space.h"

#define SPACE_MAX_CALLS 1

struct Space
{
	char call;
	char * method[SPACE_MAX_CALLS];
	size_t nextPlace[SPACE_MAX_CALLS];
	size_t gapPlace[SPACE_MAX_CALLS];
	char canTakeAnotherEntry[SPACE_MAX_CALLS];
};

struct Space * Space_mock()
{
	struct Space * this = malloc(sizeof(struct Space));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < SPACE_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->nextPlace[i] = 55555;
		this->gapPlace[i] = 55555;
		this->canTakeAnotherEntry[i] = 63;
	}

	return this;
}

void Space_destruct(struct Space * this)
{
	free(this);
	this = NULL;
}

char Space_canTakeAnotherEntry(struct Space * this, size_t nextPlace, size_t gapPlace)
{
	this->method[this->call] = "Space_canTakeAnotherEntry";
	this->nextPlace[this->call] = nextPlace;
	this->gapPlace[this->call] = gapPlace;
	
	char canTakeAnotherEntry = this->canTakeAnotherEntry[this->call];

	this->call++;
	
	return canTakeAnotherEntry;
}
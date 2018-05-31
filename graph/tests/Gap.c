#include "../source/Gap.h"

#define GAP_MAX_CALLS 3

struct Gap {
	char call;
	char * method[GAP_MAX_CALLS];
	size_t place[GAP_MAX_CALLS];
	size_t count[GAP_MAX_CALLS];
	size_t incrementedCount[GAP_MAX_CALLS];
	size_t nextGapPlace[GAP_MAX_CALLS];
};

struct Gap * Gap_mock()
{
	struct Gap * this = malloc(sizeof(struct Gap));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < GAP_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->place[i] = 55555;
		this->count[i] = 55555;
		this->incrementedCount[i] = 55555;
		this->nextGapPlace[i] = 55555;
	}

	return this;
}

void Gap_destruct(struct Gap * this)
{
	free(this);
	this = NULL;
}

void Gap_create(struct Gap * this, size_t place, size_t nextGapPlace, size_t count)
{
	this->method[this->call] = "Gap_create";
	this->place[this->call] = place;
	this->nextGapPlace[this->call] = nextGapPlace;
	this->count[this->call] = count;
	
	this->call++;
}

void Gap_read(struct Gap * this, size_t place)
{
	this->method[this->call] = "Gap_read";
	this->place[this->call] = place;
	
	this->call++;
}

void Gap_delete(struct Gap * this)
{
	this->method[this->call] = "Gap_delete";
	
	this->call++;
}

size_t Gap_increment(struct Gap * this)
{
	this->method[this->call] = "Gap_increment";
	
	size_t incrementedCount = this->incrementedCount[this->call];
	
	this->call++;
	
	return incrementedCount;
}

size_t Gap_getNext(struct Gap * this)
{
	this->method[this->call] = "Gap_getNext";
	
	size_t nextGapPlace = this->nextGapPlace[this->call];
	
	this->call++;
	
	return nextGapPlace;
}
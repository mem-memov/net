#include "../source/Direction.h"
#include <stdlib.h>
#include "../source/DirectionError.h"

#define DIRECTION_MAX_CALLS 1

struct Direction {
	char call;
	char * method[DIRECTION_MAX_CALLS];
	size_t place[DIRECTION_MAX_CALLS];
	size_t destination[DIRECTION_MAX_CALLS];
	size_t previous[DIRECTION_MAX_CALLS];
	size_t next[DIRECTION_MAX_CALLS];
	size_t node[DIRECTION_MAX_CALLS];
	size_t result[DIRECTION_MAX_CALLS];
};

struct Direction * Direction_mock()
{
	struct Direction * this = malloc(sizeof(struct Direction));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < DIRECTION_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->place[i] = 55555;
		this->destination[i] = 55555;
		this->previous[i] = 55555;
		this->next[i] = 55555;
		this->node[i] = 55555;
		this->result[i] = 55555;
	}

	return this;
}

void Direction_destruct(struct Direction * this)
{
	free(this);
	this = NULL;
}

size_t Direction_getPlace(struct Direction * this)
{
	this->method[this->call] = "Direction_getPlace";
	
	size_t place = this->place[this->call];
		
	this->call++;
	
	return place;
}

void Direction_create(struct Direction * this, size_t place, size_t destination)
{
	this->method[this->call] = "Direction_create";
	this->place[this->call] = place;
	this->destination[this->call] = destination;
	
	this->call++;
}

void Direction_read(struct Direction * this, size_t place)
{
	this->method[this->call] = "Direction_read";
	this->place[this->call] = place;
	
	this->call++;
}

void Direction_joinChain(struct Direction * this, size_t previous, size_t next)
{
	this->method[this->call] = "Direction_joinChain";
	this->previous[this->call] = previous;
	this->next[this->call] = next;
	
	this->call++;
}

void Direction_append(struct Direction * this, size_t previous)
{
	this->method[this->call] = "Direction_append";
	this->previous[this->call] = previous;
	
	this->call++;
}

char Direction_hasNode(struct Direction * this, size_t node)
{
	this->method[this->call] = "Direction_hasNode";
	this->node[this->call] = node;
	
	char result = this->result[this->call];
	
	this->call++;
	
	return result;
}

size_t Direction_getNode(struct Direction * this)
{
	this->method[this->call] = "Direction_getNode";
	
	char result = this->result[this->call];
	
	this->call++;
	
	return result;
}

size_t Direction_getNext(struct Direction * this)
{
	this->method[this->call] = "Direction_getNext";
	
	char result = this->result[this->call];
	
	this->call++;
	
	return result;
}

void Direction_delete(struct Direction * this)
{
	this->method[this->call] = "Direction_delete";
	
	this->call++;
}


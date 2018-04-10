#include "Space.h"
#include <stdlib.h>
#include "Gap.h"

struct Space * Space_construct(unsigned int size)
{
	struct Space * this = malloc(sizeof(struct Space));
	
	this->size = size;
	this->places = malloc(sizeof(unsigned int) * size);
	this->next = 1;
	this->gap = NULL;

	return this;
}

void Space_destruct(struct Space * this)
{
	if (NULL != this->gap) {
		Gap_destruct(this->gap);
	}
	
	free(this->places);
	
	free(this);
}

char Space_hasFreePlace(struct Space * this)
{
	if (this->next < this->size) {
		return 1;
	}
	
	return 0;
}

unsigned int Space_addNode(struct Space * this)
{
	unsigned int place;
	struct Gap * gap = this->gap;
	
	if (NULL != gap) {
		place = Gap_getPlace(gap);
		this->gap = Gap_getNext(gap);
		Gap_destruct(gap);
	} else {
		place = this->next;
		this->next += 2;
	}

	this->places[place] = place;
	this->places[place + 1] = 0;

	return place;
}

void Space_removeNode(struct Space * this, unsigned int place)
{
	unsigned int current = 1;
	
	while (current < this->next) {
		
		if (this->places[current] == place) {
			this->places[current] = 0;
		}
		
		current++;
	}
	
	current = 1;
	
	while (current < this->next) {
		
		if (0 == this->places[this->places[current + 1]]) {
			this->places[current + 1] = this->places[this->places[current] + 1];
			this->places[this->places[current] + 1] = 0;
		}
		
		current++;
	}
	
	current = 1;
	
	while (current < this->next) {
		
		if (0 == this->places[current] && 0 == this->places[current + 1]) {
			if (NULL == this->gap) {
				this->gap = Gap_construct(current, NULL);
			} else {
				this->gap = Gap_construct(current, this->gap);
			}
		}
		
		current++;
	}
}

void Space_connectNodes(struct Space * this, unsigned int origin, unsigned int destination)
{
	if (! Space_isNode(this, origin) || ! Space_isNode(this, destination)) {
		exit(1);
	}
	
	unsigned int last = origin;
	unsigned int place;

	while (0 != this->places[last + 1]) {
		last = this->places[last + 1];
	}

	struct Gap * gap = this->gap;
	if (NULL != gap) {
		this->places[last] = Gap_getPlace(gap);
		this->gap = Gap_getNext(gap);
		Gap_destruct(gap);
	} else {
		this->places[last] = this->next;
		this->next += 2;
	}

	place = this->places[last];
	
	this->places[place] = destination;
	this->places[place + 1] = 0;
}

void Space_disconnectNodes(struct Space * this, unsigned int origin, unsigned int destination)
{
	if (! Space_isNode(this, origin) || ! Space_isNode(this, destination)) {
		exit(1);
	}
	
	unsigned int current = origin;
	unsigned int next = this->places[origin + 1];

	while (this->places[next] != destination) {
		
		current = next;
		next = this->places[current + 1];
		
		if (next >= this->next) {
			exit(1);
		}
	}
	
	this->places[current + 1] = this->places[next + 1];
	this->places[next] = 0;
	this->places[next + 1] = 0;
	
	if (NULL == this->gap) {
		this->gap = Gap_construct(next, NULL);
	} else {
		this->gap = Gap_construct(next, this->gap);
	}
}

unsigned int Space_getNode(struct Space * this, unsigned int * place)
{
	if (! Space_isNode(this, (* place))) {
		exit(1);
	}
	
	* place = this->places[(* place)];
	
	return this->places[(* place) + 1];
}

char Space_isNode(struct Space * this, unsigned int place)
{
	if (this->places[place] == place) {
		return 1;
	}
	
	return 0;
}

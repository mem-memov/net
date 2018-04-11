#include "Space.h"
#include <stdlib.h>
#include <stdio.h>
#include "Gap.h"

struct Space * Space_construct(unsigned int size)
{
	struct Space * this = malloc(sizeof(struct Space));
	
	if (size < 1) {
		exit(0);
	}
	
	this->size = size;
	this->places = (unsigned int *)malloc(sizeof(unsigned int) * size);
	this->places[0] = 1;
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
	if (this->places[0] < this->size) {
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
		printf("%u\n", place);
		this->gap = Gap_getNext(gap);
		Gap_destruct(gap);
	} else {
		place = this->places[0];
		this->places[0] += 2;
	}

	this->places[place] = place;
	this->places[place + 1] = 0;

	return place;
}

void Space_removeNode(struct Space * this, unsigned int place)
{
	unsigned int current;
	unsigned int next;
	
	// remove the node
	
	current = place;
	
	while (0 != this->places[current + 1]) {
		this->places[current] = 0;
		this->places[current + 1] = 0;
		
		if (NULL == this->gap) {
			this->gap = Gap_construct(current, NULL);
		} else {
			this->gap = Gap_construct(current, this->gap);
		}
		
		current = this->places[current + 1];
	}
	
	// remove connections to the node
	
	current = 1;
	
	while (current < this->places[0]) {
		
		next = this->places[current + 1];
		
		if (place == next) {
			this->places[current + 1] = this->places[next + 1];
			
			this->places[next] = 0;
			this->places[next + 1] = 0;

			if (NULL == this->gap) {
				this->gap = Gap_construct(next, NULL);
			} else {
				this->gap = Gap_construct(next, this->gap);
			}
		}
		
		current += 2;
	}
}

void Space_connectNodes(struct Space * this, unsigned int origin, unsigned int destination)
{
	if (origin == destination) {
		exit(1);
	}
	
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
		this->places[last + 1] = Gap_getPlace(gap);
		this->gap = Gap_getNext(gap);
		Gap_destruct(gap);
	} else {
		this->places[last + 1] = this->places[0];
		this->places[0] += 2;
	}

	place = this->places[last + 1];
	
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
		
		if (next >= this->places[0]) {
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

unsigned int Space_getNode(struct Space * this, unsigned int next, unsigned int * place)
{
	* place = this->places[next];
	
	return this->places[next + 1];
}

char Space_isNode(struct Space * this, unsigned int place)
{
	if (this->places[place] == place && place > 0 && place < this->places[0]) {
		return 1;
	}

	return 0;
}

void Space_export(struct Space * this, FILE * file)
{
	size_t totalItems = fwrite(this->places, sizeof(unsigned int), this->places[0], file);
	
	if (totalItems != this->places[0]) {
		exit(1);
	}
}

void Space_import(struct Space * this, FILE * file)
{
	size_t headItems = fread(this->places, sizeof(unsigned int), 1, file);
	
	if (headItems != 1) {
		exit(1);
	}
	
	if (this->size < this->places[0]) {
		exit(1);
	}
	
	size_t bodyItems = fread(this->places + 1, sizeof(unsigned int), this->places[0] - 1, file);

	if (bodyItems != this->places[0] - 1) {
		exit(1);
	}
	
	unsigned int current = 1;
	
	while (current < this->places[0]) {
		
		if (0 == this->places[current] && 0 == this->places[current + 1]) {
			if (NULL == this->gap) {
				this->gap = Gap_construct(current, NULL);
			} else {
				this->gap = Gap_construct(current, this->gap);
			}
		}
		
		current += 2;
	}
}

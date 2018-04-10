#include "Gap.h"
#include <stdlib.h>

struct Gap * Gap_construct(unsigned int place, struct Gap * next)
{
	struct Gap * this = malloc(sizeof(struct Gap));
	
	this->place = place;
	this->next = next;

	return this;
}

void Gap_destruct(struct Gap * this)
{
	if (NULL != this->next) {
		Gap_destruct(this->next);
	}
	
	free(this);
}

unsigned int Gap_getPlace(struct Gap * this)
{
	unsigned int place = this->place;
	this->place = 0;
	
	return place;
}

struct Gap * Gap_getNext(struct Gap * this)
{
	struct Gap * next = this->next;
	this->next = NULL;
	
	return next;
}
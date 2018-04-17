#include "Gap.h"
#include <stdlib.h>
#include "GapError.h"

struct Gap * Gap_construct(size_t place, struct Gap * next)
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

size_t Gap_getPlace(struct Gap * this)
{
	GapError_placeCanBeReadOnlyOnce(this->place);

	size_t place = this->place;
	this->place = 0;
	
	return place;
}

struct Gap * Gap_getNext(struct Gap * this)
{
	struct Gap * next = this->next;

	this->next = NULL;
	Gap_destruct(this);
	
	return next;
}
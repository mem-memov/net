#include "Gap.h"
#include <stdlib.h>
#include "GapError.h"

struct Gap {
	size_t place;
	struct Gap * next;
	struct GapError * error;
};

struct Gap * Gap_construct(size_t place, struct Gap * next, struct GapError * error)
{
	GapError_zeroPlaceIsReservedForInvalidGap(error, place);
	
	struct Gap * this = malloc(sizeof(struct Gap));
	
	this->place = place;
	this->next = next;
	this->error = error;

	return this;
}

void Gap_destruct(struct Gap * this)
{
	if (NULL != this->next) {
		Gap_destruct(this->next);
	}

	free(this->error);
	free(this);
}

size_t Gap_getPlace(struct Gap * this)
{
	GapError_placeCanBeReadOnlyOnce(this->error, this->place);

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
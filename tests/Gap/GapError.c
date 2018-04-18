#include "../../source/GapError.h"
#include <stdlib.h>

struct GapError {
	size_t place;
	char * method;
};

struct GapError * GapError_construct()
{
	struct GapError * this = malloc(sizeof(struct GapError));

	return this;
}

void GapError_destruct(struct GapError * this)
{
	free(this->method); 
	free(this);
}

void GapError_zeroPlaceIsReservedForInvalidGap(struct GapError * this, size_t place)
{
	this->method = "GapError_zeroPlaceIsReservedForInvalidGap";
	this->place = place;
}

void GapError_placeCanBeReadOnlyOnce(struct GapError * this, size_t place)
{
	this->method = "GapError_placeCanBeReadOnlyOnce";
	this->place = place;
}
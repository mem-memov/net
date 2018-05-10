#include "Counts.h"
#include <stdlib.h>

struct Counts
{
	struct Places * places;
	struct CountError * countError;
};

struct Counts * Counts_construct(struct Places * places, struct CountError * countError)
{
	struct Counts * this = malloc(sizeof(struct Counts));
	
	this->places = places;
	this->countError = countError;

	return this;
}

void Counts_destruct(struct Counts * this)
{
	CountError_destruct(this->countError);
	
	free(this);
	this = NULL;
}

struct Count * Counts_make(struct Counts * this)
{
	return Count_construct(
		Places_make(this->places),
		this->countError
	);
}
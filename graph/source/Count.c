#include "Count.h"
#include <stdlib.h>

struct Count
{
	struct Place * place;
	struct CountError * error;
};

struct Count * Count_construct(struct Place * place, struct CountError * error)
{
	struct Count * this = malloc(sizeof(struct Count));
	
	this->place = place;
	this->error = error;

	return this;
}

void Count_destruct(struct Count * this)
{
	Place_destruct(this->place);
	
	free(this);
	this = NULL;
}

void Count_bind(struct Count * this, size_t position)
{
	Place_bind(this->place, position);
}

void Count_create(struct Count * this)
{
	Place_set(this->place, 0);
}

void Count_delete(struct Count * this)
{
	Place_set(this->place, 0);
}

void Count_increment(struct Count * this)
{
	size_t value = Place_get(this->place);
	
	// TODO: check overflow
	
	value++;
	
	Place_set(this->place, value);
}

void Count_decrement(struct Count * this)
{
	size_t value = Place_get(this->place);
	
	CountError_forbidNegativeValueWhenDecrementing(this->error, value);

	value--;
	
	Place_set(this->place, value);
}

char Count_isZero(struct Count * this)
{
	size_t value = Place_get(this->place);
	
	if ( 0 == value) {
		return 1;
	}
	
	return 0;
}

size_t Count_get(struct Count * this)
{
	return Place_get(this->place);
}
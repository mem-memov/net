#include "Gap.h"
#include <stdlib.h>

struct Gap {
	// fields
	struct Place * zero;
	struct Place * count;
	struct Place * next;
	struct Place * three;
	struct Place * four;
	struct Place * five;

	struct GapError * error;
};

struct Gap * Gap_construct(
	struct Place * zero,
	struct Place * count,
	struct Place * next,
	struct Place * three,
	struct Place * four,
	struct Place * five,
	struct GapError * error
) {
	struct Gap * this = malloc(sizeof(struct Gap));
	
	// fields
	this->zero = zero;
	this->count = count;
	this->next = next;
	this->three = three;
	this->four = four;
	this->five = five;
	
	this->error = error;

	return this;
}

void Gap_destruct(struct Gap * this)
{
	Place_destruct(this->zero);
	Place_destruct(this->count);
	Place_destruct(this->next);
	Place_destruct(this->three);
	Place_destruct(this->four);
	Place_destruct(this->five);
	
	free(this);
	this = NULL;
}

void Gap_create(struct Gap * this, size_t place, size_t nextGapPlace, size_t count)
{
	Gap_read(this, place);
	
	Place_set(this->zero, 0);
	Place_set(this->count, count);
	Place_set(this->next, nextGapPlace);
	Place_set(this->three, 0);
	Place_set(this->four, 0);
	Place_set(this->five, 0);
}

void Gap_read(struct Gap * this, size_t place)
{
	Place_bind(this->zero, place + 0);
	Place_bind(this->count, place + 1);
	Place_bind(this->next, place + 2);
	Place_bind(this->three, place + 3);
	Place_bind(this->four, place + 4);
	Place_bind(this->five, place + 5);
}

void Gap_delete(struct Gap * this)
{
	Place_set(this->zero, 0);
	Place_set(this->count, 0);
	Place_set(this->next, 0);
	Place_set(this->three, 0);
	Place_set(this->four, 0);
	Place_set(this->five, 0);
}

size_t Gap_increment(struct Gap * this)
{
	return Place_get(this->count) + 1;
}

size_t Gap_getNext(struct Gap * this)
{
	return Place_get(this->next);
}
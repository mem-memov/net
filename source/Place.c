#include "Place.h"
#include <stdlib.h>

struct Place
{
	unsigned char length;
	size_t position;
	unsigned char * bytes;
	size_t index;
};

struct Place * Place_construct(unsigned char length, unsigned char * bytes)
{
	struct Place * this = malloc(sizeof(struct Place));
	
	if (sizeof(size_t) < length) {
		exit(1);
	}
	
	this->length = length;
	this->position = 0;
	this->bytes = bytes;
	this->index = 0;
	
	return this;
}

void Place_destruct(struct Place * this)
{
	free(this);
	this = NULL;
}

void Place_bind(struct Place * this, size_t position)
{
	this->position = position;
	this->index = position * this->length;
}

size_t Place_get(struct Place * this)
{
	size_t value = 0;
	unsigned char i;
	
	for (i = 0; i < this->length; i++) {
		value = value << 8;
		value += this->bytes[this->index + i];
	}
	
	return value;
}

void Place_set(struct Place * this, size_t value)
{
	unsigned char i;
	unsigned char shift;
	
	for (i = 0; i < this->length; i++) {
		shift = 8 * (this->length - i - 1);
		this->bytes[this->index + i] = (value >> shift) & 0xFF;
	}
}

char Place_isZero(struct Place * this)
{
	unsigned char i;
	
	for (i = this->length - 1; i > 0; i--) {
		if (this->bytes[this->index + i] > 0) {
			return 0;
		}
	}
	
	return 1;
}

char Place_keepsPosition(struct Place * this)
{
	if (Place_get(this) == this->position) {
		return 1;
	}
	
	return 0;
}

void Place_increment(struct Place * this)
{
	size_t value = Place_get(this);
	
	// TODO: check overflow
	
	Place_set(this, value + 1);
}

void Place_decrement(struct Place * this)
{
	size_t value = Place_get(this);
	
	if ( 0 == value ) {
		exit(1);
	}
	
	Place_set(this, value - 1);
}
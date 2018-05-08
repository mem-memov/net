#include "../../source/Place.h"
#include <stdlib.h>

struct Place
{
	size_t value;
	size_t position;
	char * method;
};

struct Place * Place_mock()
{
	struct Place * this = malloc(sizeof(struct Place));
	
	this->value = 55555;
	this->position = 55555;
	this->method = "method not specified";
	
	return this;
}

void Place_destruct(struct Place * this)
{

}

void Place_bind(struct Place * this, size_t position)
{
	this->method = "Place_bind";
	this->position = position;
}

size_t Place_get(struct Place * this)
{
	this->method = "Place_get";
	
	return this->value;
}

void Place_set(struct Place * this, size_t value)
{
	this->method = "Place_set";
	this->value = value;
}

char Place_isZero(struct Place * this)
{

}

char Place_keepsPosition(struct Place * this)
{

}

void Place_increment(struct Place * this)
{

}

void Place_decrement(struct Place * this)
{

}
#include "../../source/Count.h"
#include <stdlib.h>

#define COUNT_MAX_CALLS 1

struct Count
{
	char call;
	char * method[COUNT_MAX_CALLS];
	size_t position[COUNT_MAX_CALLS];
	char isZero[COUNT_MAX_CALLS];
	size_t value[COUNT_MAX_CALLS];
};

struct Count * Count_mock()
{
	struct Count * this = malloc(sizeof(struct Count));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < COUNT_MAX_CALLS; i++) {
		this->method[i] = "method not specified";
		this->position[i] = 5555;
		this->isZero[i] = 27;
		this->value[i] = 5555;
	}

	return this;
}

void Count_destruct(struct Count * this)
{
	free(this);
	this = NULL;
}

void Count_bind(struct Count * this, size_t position)
{
	this->method[this->call] = "Count_bind";
	this->position[this->call] = position;
	
	this->call++;
}

void Count_create(struct Count * this)
{
	this->method[this->call] = "Count_create";
	
	this->call++;
}

void Count_delete(struct Count * this)
{
	this->method[this->call] = "Count_delete";
	
	this->call++;
}

void Count_increment(struct Count * this)
{
	this->method[this->call] = "Count_increment";
	
	this->call++;
}

void Count_decrement(struct Count * this)
{
	this->method[this->call] = "Count_decrement";
	
	this->call++;
}

char Count_isZero(struct Count * this)
{
	this->method[this->call] = "Count_isZero";
	char isZero = this->isZero[this->call];
	
	this->call++;
	
	return isZero;
}

size_t Count_get(struct Count * this)
{
	this->method[this->call] = "Count_get";
	size_t value = this->value[this->call];
	
	this->call++;
	
	return value;
}
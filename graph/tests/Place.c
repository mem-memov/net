#include "../source/Place.h"
#include <stdlib.h>

#define PLACE_MAX_CALLS 4

struct Place
{
	char call;
	char * method[PLACE_MAX_CALLS];
	size_t value[PLACE_MAX_CALLS];
	size_t position[PLACE_MAX_CALLS];
	char keepsPosition[PLACE_MAX_CALLS];
};

struct Place * Place_mock()
{
	struct Place * this = malloc(sizeof(struct Place));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < PLACE_MAX_CALLS; i++) {
		this->method[i] = "method not specified";
		this->value[i] = 55555;
		this->position[i] = 55555;
		this->keepsPosition[i] = 28;
	}

	return this;
}

void Place_destruct(struct Place * this)
{
	free(this);
	this = NULL;
}

void Place_bind(struct Place * this, size_t position)
{
	this->method[this->call] = "Place_bind";
	this->position[this->call] = position;
	
	this->call++;
}

size_t Place_get(struct Place * this)
{
	this->method[this->call] = "Place_get";
	
	size_t value = this->value[this->call];
	
	this->call++;
	
	return value;
}

void Place_set(struct Place * this, size_t value)
{
	this->method[this->call] = "Place_set";
	this->value[this->call] = value;
	
	this->call++;
}

char Place_keepsPosition(struct Place * this)
{
	this->method[this->call] = "Place_keepsPosition";
	char keepsPosition = this->keepsPosition[this->call];
	
	this->call++;
	
	return keepsPosition;
}

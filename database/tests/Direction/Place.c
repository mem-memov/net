#include "../../source/Place.h"
#include <stdlib.h>

struct Place
{
	char call;
	size_t value[3];
	size_t position[3];
	char * method[3];
};

struct Place * Place_mock()
{
	struct Place * this = malloc(sizeof(struct Place));
	
	this->call = 0;
	
	this->value[0] = 55555;
	this->position[0] = 55555;
	this->method[0] = "method not specified";
	
	this->value[1] = 55555;
	this->position[1] = 55555;
	this->method[1] = "method not specified";
	
	this->value[2] = 55555;
	this->position[2] = 55555;
	this->method[2] = "method not specified";
	
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
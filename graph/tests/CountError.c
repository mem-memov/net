#include "../source/CountError.h"

#define COUNTERROR_MAX_CALLS 1

struct CountError
{
	char call;
	char * method[COUNTERROR_MAX_CALLS];
	size_t value[COUNTERROR_MAX_CALLS];
};

struct CountError * CountError_mock()
{
	struct CountError * this = malloc(sizeof(struct CountError));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < COUNTERROR_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->value[i] = 55555;
	}

	return this;
}

void CountError_destruct(struct CountError * this)
{
	free(this);
	this = NULL;
}

void CountError_forbidNegativeValueWhenDecrementing(struct CountError * this, size_t value)
{
	this->method[this->call] = "CountError_forbidNegativeValueWhenDecrementing";
	this->value[this->call] = value;
	
	this->call++;
}


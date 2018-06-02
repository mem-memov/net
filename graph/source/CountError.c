#include "CountError.h"

struct CountError
{
	struct Error * error;
};

struct CountError * CountError_construct(struct Error * error)
{
	struct CountError * this = malloc(sizeof(struct CountError));
	
	this->error = error;

	return this;
}

void CountError_destruct(struct CountError * this)
{
	free(this);
	this = NULL;
}

void CountError_forbidNegativeValueWhenDecrementing(struct CountError * this, size_t value)
{
	if ( 0 == value) {
		Error_terminate(this->error);
	}
}


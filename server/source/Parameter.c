#include "Parameter.h"
#include <stdlib.h>

struct Parameter
{
	struct Listener * listener;
	int bufferLength;
	struct Application * application;
};

struct Parameter * Parameter_construct(
    struct Listener * listener, 
    int bufferLength,
    struct Application * application
) {
	struct Parameter * this = malloc(sizeof(struct Parameter));
	
	this->listener = listener;
	this->bufferLength = bufferLength;
	this->application = application;

	return this;
}

void Parameter_destruct(struct Parameter * this)
{
	free(this);
	this = NULL;
}

struct Listener * Parameter_getListener(struct Parameter * this)
{
	return this->listener;
}

int Parameter_getBufferLength(struct Parameter * this)
{
	return this->bufferLength;
}

struct Application * Parameter_getApplication(struct Parameter * this)
{
	return this->application;
}
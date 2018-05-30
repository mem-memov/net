#include "../source/StarError.h"

#define STARERROR_MAX_CALLS 1

struct StarError
{
	char call;
	char * method[STARERROR_MAX_CALLS];
	size_t outgoingLink[STARERROR_MAX_CALLS];
	size_t incomingLink[STARERROR_MAX_CALLS];
	size_t index[STARERROR_MAX_CALLS];
	size_t maxIndex[STARERROR_MAX_CALLS];
};

struct StarError * StarError_mock()
{
	struct StarError * this = malloc(sizeof(struct StarError));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < STARERROR_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->outgoingLink[i] = 55555;
		this->incomingLink[i] = 55555;
		this->index[i] = 55555;
		this->maxIndex[i] = 55555;
	}

	return this;
}

void StarError_destruct(struct StarError * this)
{
	free(this);
	this = NULL;
}

void StarError_forbidShortDestinationList(struct StarError * this, size_t outgoingLink, size_t index, size_t maxIndex)
{
	this->method[this->call] = "StarError_forbidShortDestinationList";
	this->outgoingLink[this->call] = outgoingLink;
	this->index[this->call] = index;
	this->maxIndex[this->call] = maxIndex;
	
	this->call++;
}

void StarError_forbidLongDestinationList(struct StarError * this, size_t outgoingLink)
{
	this->method[this->call] = "StarError_forbidLongDestinationList";
	this->outgoingLink[this->call] = outgoingLink;
	
	this->call++;
}

void StarError_forbidShortOriginList(struct StarError * this, size_t incomingLink, size_t index, size_t maxIndex)
{
	this->method[this->call] = "StarError_forbidShortOriginList";
	this->incomingLink[this->call] = incomingLink;
	this->index[this->call] = index;
	this->maxIndex[this->call] = maxIndex;
	
	this->call++;
}

void StarError_forbidLongOriginList(struct StarError * this, size_t incomingLink)
{
	this->method[this->call] = "StarError_forbidLongOriginList";
	this->incomingLink[this->call] = incomingLink;
	
	this->call++;
}
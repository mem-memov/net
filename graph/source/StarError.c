#include "StarError.h"

struct StarError
{
	struct Error * error;
};

struct StarError * StarError_construct(struct Error * error)
{
	struct StarError * this = malloc(sizeof(struct StarError));
	
	this->error = error;

	return this;
}

void StarError_destruct(struct StarError * this)
{
	free(this);
	this = NULL;
}

void StarError_forbidShortDestinationList(struct StarError * this, size_t outgoingLink, size_t index, size_t maxIndex)
{
	if ( 0 == outgoingLink && index != maxIndex ) {
		Error_terminate(this->error);
	}
}

void StarError_forbidLongDestinationList(struct StarError * this, size_t outgoingLink)
{
	if ( 0 != outgoingLink ) {
		Error_terminate(this->error);
	}
}

void StarError_forbidShortOriginList(struct StarError * this, size_t incomingLink, size_t index, size_t maxIndex)
{
	if ( 0 == incomingLink && index != maxIndex ) {
		Error_terminate(this->error);
	}
}

void StarError_forbidLongOriginList(struct StarError * this, size_t incomingLink)
{
	if ( 0 != incomingLink ) {
		Error_terminate(this->error);
	}
}
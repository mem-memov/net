#include "NetError.h"

struct NetError
{
	struct Error * error;
};

struct NetError * NetError_construct(struct Error * error)
{
	struct NetError * this = malloc(sizeof(struct NetError));
	
	this->error = error;

	return this;
}

void NetError_destruct(struct NetError * this)
{
	free(this);
	this = NULL;
}

void NetError_requireOneToVerifyCorrectPlaceSize(struct NetError * this, size_t one)
{
	if ( 1 != one ) {
		Error_terminate(this->error);
	}
}

void NetError_requireFreeSpaceAvailable(struct NetError * this, char isAvailable)
{
	if ( ! isAvailable ) {
		Error_terminate(this->error);
	}
}
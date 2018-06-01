#include "BoatError.h"

struct BoatError
{
	struct Error * error;
};

struct BoatError * BoatError_construct(struct Error * error)
{
	struct BoatError * this = malloc(sizeof(struct BoatError));
	
	this->error = error;

	return this;
}

void BoatError_destruct(struct BoatError * this)
{
	free(this);
	this = NULL;
}

void BoatError_requireOboatoVerifyCorrectPlaceSize(struct BoatError * this, size_t one)
{
	if ( 1 != one ) {
		Error_terminate(this->error);
	}
}

void BoatError_requireFreeSpaceAvailable(struct BoatError * this, char isAvailable)
{
	if ( ! isAvailable ) {
		Error_terminate(this->error);
	}
}
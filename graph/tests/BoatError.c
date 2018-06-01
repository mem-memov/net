#include "../source/BoatError.h"

#define BOATERROR_MAX_CALLS 2

struct BoatError
{
	char call;
	char * method[BOATERROR_MAX_CALLS];
	size_t one[BOATERROR_MAX_CALLS];
	size_t isAvailable[BOATERROR_MAX_CALLS];
};

struct BoatError * BoatError_mock()
{
	struct BoatError * this = malloc(sizeof(struct BoatError));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < BOATERROR_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->one[i] = 55555;
		this->isAvailable[i] = 47;
	}

	return this;
}

void BoatError_destruct(struct BoatError * this)
{
	free(this);
	this = NULL;
}

void BoatError_requireOboatoVerifyCorrectPlaceSize(struct BoatError * this, size_t one)
{
	this->method[this->call] = "BoatError_requireOboatoVerifyCorrectPlaceSize";
	this->one[this->call] = one;
	
	this->call++;
}

void BoatError_requireFreeSpaceAvailable(struct BoatError * this, char isAvailable)
{
	this->method[this->call] = "BoatError_requireFreeSpaceAvailable";
	this->isAvailable[this->call] = isAvailable;
	
	this->call++;
}
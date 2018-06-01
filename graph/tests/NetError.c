#include "../source/NetError.h"

#define NETERROR_MAX_CALLS 2

struct NetError
{
	char call;
	char * method[NETERROR_MAX_CALLS];
	size_t one[NETERROR_MAX_CALLS];
	size_t isAvailable[NETERROR_MAX_CALLS];
};

struct NetError * NetError_mock()
{
	struct NetError * this = malloc(sizeof(struct NetError));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < NETERROR_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->one[i] = 55555;
		this->isAvailable[i] = 47;
	}

	return this;
}

void NetError_destruct(struct NetError * this)
{
	free(this);
	this = NULL;
}

void NetError_requireOneToVerifyCorrectPlaceSize(struct NetError * this, size_t one)
{
	this->method[this->call] = "NetError_requireOneToVerifyCorrectPlaceSize";
	this->one[this->call] = one;
	
	this->call++;
}

void NetError_requireFreeSpaceAvailable(struct NetError * this, char isAvailable)
{
	this->method[this->call] = "NetError_requireFreeSpaceAvailable";
	this->isAvailable[this->call] = isAvailable;
	
	this->call++;
}
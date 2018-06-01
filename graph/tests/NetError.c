#include "../source/NetError.h"

#define NETERROR_MAX_CALLS 1

struct NetError
{
	char call;
	char * method[NETERROR_MAX_CALLS];
	size_t nextPlace[NETERROR_MAX_CALLS];
	size_t graphSize[NETERROR_MAX_CALLS];
};

struct NetError * NetError_mock()
{
	struct NetError * this = malloc(sizeof(struct NetError));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < NETERROR_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->nextPlace[i] = 55555;
		this->graphSize[i] = 55555;
	}
	
	return this;
}

void NetError_destruct(struct NetError * this)
{
	free(this);
	this = NULL;
}

void NetError_requireFittingInSize(struct NetError * this, size_t nextPlace, size_t graphSize)
{
	this->method[this->call] = "NetError_requireFittingInSize";
	this->nextPlace[this->call] = nextPlace;
	this->graphSize[this->call] = graphSize;
	
	this->call++;
}
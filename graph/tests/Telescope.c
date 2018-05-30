#include "../source/Telescope.h"
#include <stdlib.h>

#define TELESCOPE_MAX_CALLS 1

struct Telescope
{
	char call;
	char * method[TELESCOPE_MAX_CALLS];
	size_t incomingLink[TELESCOPE_MAX_CALLS];
	size_t originNode[TELESCOPE_MAX_CALLS];
	size_t foundIncomingLink[TELESCOPE_MAX_CALLS];
	size_t outgoingLink[TELESCOPE_MAX_CALLS];
	size_t destinationNode[TELESCOPE_MAX_CALLS];
	size_t foundOutgoingLink[TELESCOPE_MAX_CALLS];
};

struct Telescope * Telescope_mock()
{
	struct Telescope * this = malloc(sizeof(struct Telescope));

	this->call = 0;
	
	char i;
	for (i = 0; i < TELESCOPE_MAX_CALLS; i++) {
		this->method[i] = "method not specified";
		this->incomingLink[i] = 55555;
		this->originNode[i] = 55555;
		this->foundIncomingLink[i] = 55555;
		this->outgoingLink[i] = 55555;
		this->destinationNode[i] = 55555;
		this->foundOutgoingLink[i] = 55555;
	}
	
	return this;
}

void Telescope_destruct(struct Telescope * this)
{
	free(this);
	this = NULL;
}

size_t Telescope_findIncomingLink(struct Telescope * this, size_t incomingLink, size_t originNode)
{
	this->method[this->call] = "Telescope_findIncomingLink";
	
	this->incomingLink[this->call] = incomingLink;
	this->originNode[this->call] = originNode;
	
	size_t foundIncomingLink = this->foundIncomingLink[this->call];
	
	this->call++;
	
	return foundIncomingLink;
}

size_t Telescope_findOutgoingLink(struct Telescope * this, size_t outgoingLink, size_t destinationNode)
{
	this->method[this->call] = "Telescope_findOutgoingLink";
	
	this->outgoingLink[this->call] = outgoingLink;
	this->destinationNode[this->call] = destinationNode;
	
	size_t foundOutgoingLink = this->foundOutgoingLink[this->call];
	
	this->call++;
	
	return foundOutgoingLink;
}
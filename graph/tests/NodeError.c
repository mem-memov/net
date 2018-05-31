#include "../source/NodeError.h"
#include <stdlib.h>

#define NODEERROR_MAX_CALLS 1

struct NodeError {
	char call;
	char * method[NODEERROR_MAX_CALLS];
	size_t outgoingLink[NODEERROR_MAX_CALLS];
	size_t incomingLink[NODEERROR_MAX_CALLS];
	size_t outgoingLinkCount[NODEERROR_MAX_CALLS];
	size_t incomingLinkCount[NODEERROR_MAX_CALLS];
};

struct NodeError * NodeError_mock()
{
	struct NodeError * this = malloc(sizeof(struct NodeError));

	this->call = 0;
	
	char i;
	for (i = 0; i < NODEERROR_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->outgoingLink[i] = 55555;
		this->incomingLink[i] = 55555;
		this->outgoingLinkCount[i] = 55555;
		this->incomingLinkCount[i] = 55555;
	}

	return this;
}

void NodeError_destruct(struct NodeError * this)
{
	free(this);
	this = NULL;
}

void NodeError_forbidDeletingNodeWithConnections(struct NodeError * this, size_t outgoingLink, size_t incomingLink)
{
	this->method[this->call] = "NodeError_forbidDeletingNodeWithConnections";
	this->outgoingLink[this->call] = outgoingLink;
	this->incomingLink[this->call] = incomingLink;
	
	this->call++;
}

void NodeError_forbidReadingOutgoingLinkWhenNonePresent(struct NodeError * this, size_t outgoingLink)
{
	this->method[this->call] = "NodeError_forbidReadingOutgoingLinkWhenNonePresent";
	this->outgoingLink[this->call] = outgoingLink;
	
	this->call++;
}

void NodeError_forbidReadingIncomingLinkWhenNonePresent(struct NodeError * this, size_t incomingLink)
{
	this->method[this->call] = "NodeError_forbidReadingIncomingLinkWhenNonePresent";
	this->incomingLink[this->call] = incomingLink;
	
	this->call++;
}

void NodeError_forbidDeletingOutgoingLinkWhenNonePresent(struct NodeError * this, size_t outgoingLinkCount)
{
	this->method[this->call] = "NodeError_forbidDeletingOutgoingLinkWhenNonePresent";
	this->outgoingLinkCount[this->call] = outgoingLinkCount;
	
	this->call++;
}

void NodeError_forbidDeletingIncomingLinkWhenNonePresent(struct NodeError * this, size_t incomingLinkCount)
{
	this->method[this->call] = "NodeError_forbidDeletingIncomingLinkWhenNonePresent";
	this->incomingLinkCount[this->call] = incomingLinkCount;
	
	this->call++;
}

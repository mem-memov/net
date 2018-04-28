#include "../../source/NodeError.h"
#include <stdlib.h>

struct NodeError {
	size_t outgoingLink;
	size_t incomingLink;
	char * method;
};

struct NodeError * NodeError_mock()
{
	struct NodeError * this = malloc(sizeof(struct NodeError));

	this->outgoingLink = 55555;
	this->incomingLink = 55555;
	
	return this;
}

void NodeError_destruct(struct NodeError * this)
{
	free(this);
	this = NULL;
}

void NodeError_forbidDeletingNodeWithConnections(struct NodeError * this, size_t outgoingLink, size_t incomingLink)
{
	this->method = "NodeError_forbidDeletingNodeWithConnections";
	this->outgoingLink = outgoingLink;
	this->incomingLink = incomingLink;
}

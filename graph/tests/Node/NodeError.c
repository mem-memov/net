#include "../../source/NodeError.h"
#include <stdlib.h>

struct NodeError {
	size_t outgoingLink;
	size_t incomingLink;
	size_t outgoingLinkCount;
	size_t incomingLinkCount;
	char * method;
};

struct NodeError * NodeError_mock()
{
	struct NodeError * this = malloc(sizeof(struct NodeError));

	this->outgoingLink = 55555;
	this->incomingLink = 55555;
	this->outgoingLinkCount = 55555;
	this->incomingLinkCount = 55555;
	
	this->method = "method not specified";
	
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

void NodeError_forbidReadingOutgoingLinkWhenNonePresent(struct NodeError * this, size_t outgoingLink)
{
	this->method = "NodeError_forbidReadingOutgoingLinkWhenNonePresent";
	this->outgoingLink = outgoingLink;
}

void NodeError_forbidReadingIncomingLinkWhenNonePresent(struct NodeError * this, size_t incomingLink)
{
	this->method = "NodeError_forbidReadingIncomingLinkWhenNonePresent";
	this->incomingLink = incomingLink;
}

void NodeError_forbidDeletingOutgoingLinkWhenNonePresent(struct NodeError * this, size_t outgoingLinkCount)
{
	this->method = "NodeError_forbidDeletingOutgoingLinkWhenNonePresent";
	this->outgoingLinkCount = outgoingLinkCount;
}

void NodeError_forbidDeletingIncomingLinkWhenNonePresent(struct NodeError * this, size_t incomingLinkCount)
{
	this->method = "NodeError_forbidDeletingIncomingLinkWhenNonePresent";
	this->incomingLinkCount = incomingLinkCount;
}

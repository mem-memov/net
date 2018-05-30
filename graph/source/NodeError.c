#include "NodeError.h"

struct NodeError {
	struct Error * error;
};

struct NodeError * NodeError_construct(struct Error * error)
{
	struct NodeError * this = malloc(sizeof(struct NodeError));
	
	this->error = error;

	return this;
}

void NodeError_destruct(struct NodeError * this)
{
	free(this);
	this = NULL;
}

void NodeError_forbidDeletingNodeWithConnections(struct NodeError * this, size_t outgoingLink, size_t incomingLink)
{
	if ( 0 != outgoingLink || 0 != incomingLink ) {
		Error_terminate(this->error);
	}
}

void NodeError_forbidReadingOutgoingLinkWhenNonePresent(struct NodeError * this, size_t outgoingLink)
{
	if (0 == outgoingLink) {
		Error_terminate(this->error);
	}
}

void NodeError_forbidReadingIncomingLinkWhenNonePresent(struct NodeError * this, size_t incomingLink)
{
	if (0 == incomingLink) {
		Error_terminate(this->error);
	}
}

void NodeError_forbidDeletingOutgoingLinkWhenNonePresent(struct NodeError * this, size_t outgoingLinkCount)
{
	if (0 == outgoingLinkCount) {
		Error_terminate(this->error);
	}
}

void NodeError_forbidDeletingIncomingLinkWhenNonePresent(struct NodeError * this, size_t incomingLinkCount)
{
	if (0 == incomingLinkCount) {
		Error_terminate(this->error);
	}
}

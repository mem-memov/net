#include "NodeError.h"
#include <stdlib.h>

struct NodeError {

};

struct NodeError * NodeError_construct()
{
	struct NodeError * this = malloc(sizeof(struct NodeError));

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
		exit(1);
	}
}

void NodeError_forbidReadingOutgoingLinkWhenNonePresent(struct NodeError * this, size_t outgoingLink)
{
	if (0 == outgoingLink) {
		exit(1);
	}
}

void NodeError_forbidReadingIncomingLinkWhenNonePresent(struct NodeError * this, size_t incomingLink)
{
	if (0 == incomingLink) {
		exit(1);
	}
}

void NodeError_forbidDeletingOutgoingLinkWhenNonePresent(struct NodeError * this, size_t outgoingLinkCount)
{
	if (0 == outgoingLinkCount) {
		exit(1);
	}
}

void NodeError_forbidDeletingIncomingLinkWhenNonePresent(struct NodeError * this, size_t incomingLinkCount)
{
	if (0 == incomingLinkCount) {
		exit(1);
	}
}

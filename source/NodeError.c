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

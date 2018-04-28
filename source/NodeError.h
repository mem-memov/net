#ifndef NODEERROR_H
#define NODEERROR_H

#include <stdlib.h>

struct NodeError;

struct NodeError * NodeError_construct();

void NodeError_destruct(struct NodeError * this);

void NodeError_forbidDeletingNodeWithConnections(struct NodeError * this, size_t outgoingLink, size_t incomingLink);

void NodeError_forbidReadingOutgoingLinkWhenNonePresent(struct NodeError * this, size_t outgoingLink);

void NodeError_forbidReadingIncomingLinkWhenNonePresent(struct NodeError * this, size_t incomingLink);

void NodeError_forbidDeletingOutgoingLinkWhenNonePresent(struct NodeError * this, size_t outgoingLinkCount);

void NodeError_forbidDeletingIncomingLinkWhenNonePresent(struct NodeError * this, size_t incomingLinkCount);

#endif
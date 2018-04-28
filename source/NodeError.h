#ifndef NODEERROR_H
#define NODEERROR_H

#include <stdlib.h>

struct NodeError;

struct NodeError * NodeError_construct();

void NodeError_destruct(struct NodeError * this);

void NodeError_forbidDeletingNodeWithConnections(struct NodeError * this, size_t outgoingLink, size_t incomingLink);

#endif
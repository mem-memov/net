#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include "Count.h"
#include "NodeError.h"
#include "Place.h"
#include "Star.h"

struct Node;

struct Node * Node_construct(
	struct Place * place,
	struct Place * data,
	struct Count * outgoingLinkCount,
	struct Count * incomingLinkCount,
	struct Place * outgoingLink,
	struct Place * incomingLink,
	struct Star * star,
	struct NodeError * error
);

void Node_destruct(struct Node * this);

void Node_create(struct Node * this, size_t place);

void Node_read(struct Node * this, size_t place);

void Node_delete(struct Node * this);

size_t Node_getPlace(struct Node * this);

char Node_isNode(struct Node * this);

void Node_addIncomingLink(struct Node * this, struct Link * link);

void Node_addOutgoingLink(struct Node * this, struct Link * link);

void Node_readOutgoingLink(struct Node * this, struct Link * link);

void Node_readIncomingLink(struct Node * this, struct Link * link);

size_t Node_deleteDestination(struct Node * this, size_t destinationNode);

void Node_deleteIncomingLink(struct Node * this);

size_t Node_deleteOrigin(struct Node * this, size_t originNode);

void Node_deleteOutgoingLink(struct Node * this);

void Node_getNodeDestinations(struct Node * this, size_t ** destinations, size_t * length);

void Node_getNodeOrigins(struct Node * this, size_t ** origins, size_t * length);

char Node_isSmallOrigin(struct Node * this, struct Node * destination);

#endif
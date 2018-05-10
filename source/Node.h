#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include "Count.h"
#include "Link.h"
#include "NodeError.h"
#include "Place.h"

struct Node;

struct Node * Node_construct(
	struct Place * place,
	struct Place * data,
	struct Count * outgoingLinkCount,
	struct Count * incomingLinkCount,
	struct Place * outgoingLink,
	struct Place * incomingLink,
	struct Link * link,
	struct NodeError * error
);

void Node_destruct(struct Node * this);

void Node_create(struct Node * this, size_t place);

void Node_read(struct Node * this, size_t place);

void Node_delete(struct Node * this);

size_t Node_getPlace(struct Node * this);

char Node_isNode(struct Node * this);

char Node_hasIncomingLink(struct Node * this);

char Node_hasOutgoingLink(struct Node * this);

void Node_addIncomingLink(struct Node * this, struct Link * link);

void Node_addOutgoingLink(struct Node * this, struct Link * link);

size_t Node_findIncomingLink(struct Node * this, size_t origin);

size_t Node_findOutgoingLink(struct Node * this, size_t destination);

char Node_hasMoreOutgoingLinks(struct Node * this);

void Node_readOutgoingLink(struct Node * this, struct Link * link);

void Node_readIncomingLink(struct Node * this, struct Link * link);

void Node_deleteOutgoingLink(struct Node * this);

void Node_deleteIncomingLink(struct Node * this);

#endif
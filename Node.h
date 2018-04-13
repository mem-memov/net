#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

struct Node {
	size_t * place;
	size_t * data;
	size_t * outgoingLinkCount;
	size_t * incomingLinkCount;
	size_t * outgoingLink;
	size_t * incomingLink;
        
	size_t * places;
	
	struct Link * link;
};

struct Node * Node_construct(size_t * places);

void Node_destruct(struct Node * this);

void Node_create(struct Node * this, size_t place);

void Node_read(struct Node * this, size_t place);

size_t Node_getPlace(struct Node * this);

char Node_isNode(struct Node * this);

char Node_isSame(struct Node * this, struct Node * that);

void Node_addIncomingLink(struct Node * this, struct Link * link);

void Node_addOutgoingLink(struct Node * this, struct Link * link);

#endif
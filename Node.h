#ifndef NODE_H
#define NODE_H

struct Node {
	size_t * place;
	size_t * data;
	size_t * outCount;
	size_t * inCount;
	size_t * outLink;
	size_t * inLink;
        
	size_t * places;
};

struct Node * Node_construct(size_t * places);

void Node_destruct(struct Node * this);

void Node_create(struct Node * this, size_t place);

void Node_read(struct Node * this, size_t place);

size_t Node_getPlace(struct Node * this);

char Node_isSame(struct Node * this, struct Node * that);

void Node_addInLink(struct Node * this, struct Link * link);

void Node_addOutLink(struct Node * this, struct Link * link);

#endif
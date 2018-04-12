#ifndef LINK_H
#define LINK_H

struct Link {
	size_t * places;
        
        size_t place;
	
	// origin chain
	size_t * inNode;
	size_t * outPrevious;
	size_t * outNext;
	
	// destination chain
	size_t * outNode;
	size_t * inPrevious;
	size_t * inNext;
};

struct Link * Link_construct(size_t * places);

void Link_destruct(struct Link * this);

void Link_bind(struct Link * this, size_t place);

size_t Link_getPlace(struct Node * this);

void Link_create(struct Link * this, struct Node * originNode, struct Node * destinationNode);

void Link_read(struct Link * this, size_t place);

#endif
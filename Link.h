#ifndef LINK_H
#define LINK_H

#include <stdlib.h>

struct Link {
	size_t * places;
        
	size_t place;
	
	// origin chain
	size_t * incomingNode;
	size_t * outgoingPrevious;
	size_t * outgoingNext;
	
	// destination chain
	size_t * outgoingNode;
	size_t * incomingPrevious;
	size_t * incomingNext;
};

struct Link * Link_construct(size_t * places);

void Link_destruct(struct Link * this);

void Link_bind(struct Link * this, size_t place);

size_t Link_getPlace(struct Link * this);

void Link_create(struct Link * this, size_t place, size_t origin, size_t destination);

void Link_joinOutgoingChain(struct Link * this, size_t previous, size_t next);

void Link_joinIncomingChain(struct Link * this, size_t previous, size_t next);

void Link_moveBackwardsInOutgoingChain(struct Link * this, size_t previous);

void Link_moveBackwardsInIncomingChain(struct Link * this, size_t previous);

void Link_read(struct Link * this, size_t place);

#endif
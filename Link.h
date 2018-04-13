#ifndef LINK_H
#define LINK_H

#include <stdlib.h>

struct Link {
	size_t * places;
        
	size_t place;
	
	// pool
	struct Node * originNode;
	struct Node * destinationNode;
	struct Outgoing * outgoing;
	struct Outgoing * previousOutgoing;
	struct Outgoing * nextOutgoing;
	struct Incoming * incoming;	
	struct Incoming * previousIncoming;	
	struct Incoming * nextIncoming;
};

struct Link * Link_construct(size_t * places);

void Link_destruct(struct Link * this);

void Link_bind(struct Link * this, size_t place);

size_t Link_getPlace(struct Link * this);

void Link_create(struct Link * this, size_t place, size_t origin, size_t destination);

void Link_joinOutgoing(struct Link * this, size_t previous, size_t next);

void Link_joinIncoming(struct Link * this, size_t previous, size_t next);

void Link_moveBackwardsInOutgoing(struct Link * this, size_t previous);

void Link_moveBackwardsInIncoming(struct Link * this, size_t previous);

void Link_read(struct Link * this, size_t place);

char Link_isOutgoingToNode(struct Link * this, size_t destination);

#endif
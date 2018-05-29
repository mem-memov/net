#include "Node.h"
#include <stdlib.h>

struct Node {
	// fields
	struct Place * place;
	struct Place * data;
	struct Count * outgoingLinkCount;
	struct Count * incomingLinkCount;
	struct Place * outgoingLink;
	struct Place * incomingLink;
	
	// pool
	struct Star * star;
	
	// error
	struct NodeError * error;
};

struct Node * Node_construct(
	struct Place * place,
	struct Place * data,
	struct Count * outgoingLinkCount,
	struct Count * incomingLinkCount,
	struct Place * outgoingLink,
	struct Place * incomingLink,
	struct Star * star,
	struct NodeError * error
) {
	struct Node * this = malloc(sizeof(struct Node));

	// fields
	this->place = place;
	this->data = data;
	this->outgoingLinkCount = outgoingLinkCount;
	this->incomingLinkCount = incomingLinkCount;
	this->outgoingLink = outgoingLink;
	this->incomingLink = incomingLink;
	
	this->star = star;
	
	// pool
	this->error = error;

	// error
	return this;
}

void Node_destruct(struct Node * this)
{
	Place_destruct(this->place);
	Place_destruct(this->data);
	Count_destruct(this->outgoingLinkCount);
	Count_destruct(this->incomingLinkCount);
	Place_destruct(this->outgoingLink);
	Place_destruct(this->incomingLink);
	Star_destruct(this->star);
	
	free(this);
	this = NULL;
}

void Node_create(struct Node * this, size_t place)
{
	Node_read(this, place);

	Place_set(this->place, place);
	Place_set(this->data, 0);
	Count_create(this->outgoingLinkCount);
	Count_create(this->incomingLinkCount);
	Place_set(this->outgoingLink, 0);
	Place_set(this->incomingLink, 0);
}

void Node_read(struct Node * this, size_t place)
{
	Place_bind(this->place, place + 0);
	Place_bind(this->data, place + 1);
	Count_bind(this->outgoingLinkCount, place + 2);
	Count_bind(this->incomingLinkCount, place + 3);
	Place_bind(this->outgoingLink, place + 4);
	Place_bind(this->incomingLink, place + 5);
}

void Node_delete(struct Node * this)
{
	NodeError_forbidDeletingNodeWithConnections(this->error, Place_get(this->outgoingLink), Place_get(this->incomingLink));

	Place_set(this->place, 0);
	Place_set(this->data, 0);
	Count_delete(this->outgoingLinkCount);
	Count_delete(this->incomingLinkCount);
}

size_t Node_getPlace(struct Node * this)
{
	return Place_get(this->place);
}

char Node_isNode(struct Node * this)
{
	if ( Place_keepsPosition(this->place) && 0 != Place_get(this->place) ) {
		return 1;
	}
	
	return 0;
}

void Node_addIncomingLink(struct Node * this, struct Link * link)
{
	size_t node = Place_get(this->place);
	size_t newIncomingLink = Link_getPlace(link);
	size_t oldIncomingLink;
	
	if ( Count_isZero(this->incomingLinkCount) ) {
		Link_shiftIncoming(link, node);
	} else {
		oldIncomingLink = Place_get(this->incomingLink);
		Link_joinIncoming(link, node, oldIncomingLink);
		Star_addIncomingLink(this->star, oldIncomingLink, newIncomingLink);
	}
	
	Place_set(this->incomingLink, newIncomingLink);
	Count_increment(this->incomingLinkCount);
}

void Node_addOutgoingLink(struct Node * this, struct Link * link)
{
	size_t node = Place_get(this->place);
	size_t newOutgoingLink = Link_getPlace(link);
	size_t oldOutgoingLink;
	
	if ( Count_isZero(this->outgoingLinkCount) ) {
		Link_shiftOutgoing(link, node);
	} else {
		oldOutgoingLink = Place_get(this->outgoingLink);
		Link_joinOutgoing(link, node, oldOutgoingLink);
		Star_addOutgoingLink(this->star, oldOutgoingLink, newOutgoingLink);
	}
	
	Place_set(this->outgoingLink, newOutgoingLink);
	Count_increment(this->outgoingLinkCount);
}

size_t Node_findIncomingLink(struct Node * this, size_t origin)
{
	if ( Count_isZero(this->incomingLinkCount) ) {
		return 0;
	}

	size_t incomingLink = Place_get(this->incomingLink);
	
	return Star_findIncomingLink(this->star, incomingLink, origin);
}

size_t Node_findOutgoingLink(struct Node * this, size_t destination)
{
	if ( Count_isZero(this->outgoingLinkCount) ) {
		return 0;
	}

	size_t outgoingLink = Place_get(this->outgoingLink);
	
	return Star_findOutgoingLink(this->star, outgoingLink, destination);
}

void Node_readOutgoingLink(struct Node * this, struct Link * link)
{
	size_t outgoingLinkPlace = Place_get(this->outgoingLink);
	
	NodeError_forbidReadingOutgoingLinkWhenNonePresent(this->error, outgoingLinkPlace);
	
	Link_read(link, outgoingLinkPlace);
}

void Node_readIncomingLink(struct Node * this, struct Link * link)
{
	size_t incomingLinkPlace = Place_get(this->incomingLink);
	
	NodeError_forbidReadingIncomingLinkWhenNonePresent(this->error, incomingLinkPlace);
	
	Link_read(link, incomingLinkPlace);
}

size_t Node_deleteDestination(struct Node * this, size_t destinationNode)
{
	NodeError_forbidDeletingOutgoingLinkWhenNonePresent(this->error, Count_get(this->outgoingLinkCount));
	
	size_t outgoingLink = Place_get(this->outgoingLink);
	
	size_t deletedOutgoingLink = Star_deleteOutgoingLink(this->star, outgoingLink, destinationNode);
	
	if ( 0 == deletedOutgoingLink ) {
		return 0;
	}
	
	Count_decrement(this->outgoingLinkCount);

	if ( Count_isZero(this->outgoingLinkCount) ) {
		Place_set(this->outgoingLink, 0);
	}

	return deletedOutgoingLink;
}

void Node_deleteIncomingLink(struct Node * this)
{
	NodeError_forbidDeletingIncomingLinkWhenNonePresent(this->error, Count_get(this->incomingLinkCount));
	
	Count_decrement(this->incomingLinkCount);
	
	if ( Count_isZero(this->incomingLinkCount) ) {
		Place_set(this->incomingLink, 0);
	}
}

size_t Node_deleteOrigin(struct Node * this, size_t originNode)
{
	NodeError_forbidDeletingIncomingLinkWhenNonePresent(this->error, Count_get(this->incomingLinkCount));
	
	size_t incomingLink = Place_get(this->incomingLink);
	
	size_t deletedIncomingLink = Star_deleteIncomingLink(this->star, incomingLink, originNode);
	
	if ( 0 == deletedIncomingLink ) {
		return 0;
	}
	
	Count_decrement(this->incomingLinkCount);

	if ( Count_isZero(this->incomingLinkCount) ) {
		Place_set(this->incomingLink, 0);
	}
	
	return deletedIncomingLink;
}

void Node_deleteOutgoingLink(struct Node * this)
{
	NodeError_forbidDeletingOutgoingLinkWhenNonePresent(this->error, Count_get(this->outgoingLinkCount));
	
	Count_decrement(this->outgoingLinkCount);
	
	if ( Count_isZero(this->outgoingLinkCount) ) {
		Place_set(this->outgoingLink, 0);
	}
}

void Node_getNodeDestinations(struct Node * this, size_t ** destinations, size_t * length)
{
	(*length) = Count_get(this->outgoingLinkCount);
	
	(*destinations) = malloc(sizeof(size_t) * (*length));
	
	if ( 0 == (*length) ) {
		return;
	}
	
	size_t outgoingLinkPlace = Place_get(this->outgoingLink);
	
	Star_getNodeDestinations(this->star, outgoingLinkPlace, (*destinations), (*length));
}

void Node_getNodeOrigins(struct Node * this, size_t ** origins, size_t * length)
{
	size_t incomingLinkPlace = Place_get(this->incomingLink);
	
	(*length) = Count_get(this->incomingLinkCount);
	
	(*origins) = malloc(sizeof(size_t) * (*length));
	
	if ( 0 == incomingLinkPlace ) {
		(*length) = 0;
		return;
	}
	
	Star_getNodeOrigins(this->star, incomingLinkPlace, (*origins), (*length));
}

char Node_isSmallOrigin(struct Node * this, struct Node * destination)
{
	size_t originOutgoingLinkCount = Count_get(this->outgoingLinkCount);
	size_t destinationIncomingLinkCount = Count_get(destination->incomingLinkCount);

	if ( originOutgoingLinkCount < destinationIncomingLinkCount ) {
		return 1;
	}
	
	return 0;
}
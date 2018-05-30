#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Star.c"
#include "../Link.c"
#include "../StarError.c"
#include "../Telescope.c"

struct Star * star;
struct Link * incomingLink;
struct Link * outgoingLink;
struct Telescope * telescope;
struct StarError * starError;

void prepareTest()
{
	incomingLink = Link_mock();
	outgoingLink = Link_mock();
	telescope = Telescope_mock();
	starError = StarError_mock();
	
	star = Star_construct(incomingLink, outgoingLink, telescope, starError);
}

void demolishTest()
{
	Star_destruct(star);
	StarError_destruct(starError);
}

void it_adds_incoming_links()
{
	prepareTest();
		
	size_t oldIncomingLink = 18;
	size_t newIncomingLink = 24;
	
	Star_addIncomingLink(star, oldIncomingLink, newIncomingLink);
	
	assert(
		0 == strcmp(incomingLink->method[0], "Link_read") 
		&& incomingLink->place[0] == oldIncomingLink
	);
	
	demolishTest();
}

void it_adds_outgoing_links()
{
	prepareTest();
		
	size_t oldOutgoingLink = 18;
	size_t newOutgoingLink = 24;
	
	Star_addOutgoingLink(star, oldOutgoingLink, newOutgoingLink);
	
	assert(
		0 == strcmp(outgoingLink->method[0], "Link_read") 
		&& outgoingLink->place[0] == oldOutgoingLink
	);
	
	demolishTest();
}

void it_finds_destinations()
{
	prepareTest();
	
	size_t outgoingLinkPlace = 24;
	size_t nextOutgoingLinkPlace = 120;
	size_t length = 2;
	size_t * destinations = malloc(sizeof(size_t) * length);
	size_t destination = 36;
	size_t nextDestination = 126;
	
	outgoingLink->destinationNode[1] = destination;
	outgoingLink->nextOutgoingLink[2] = nextOutgoingLinkPlace;
	outgoingLink->destinationNode[4] = nextDestination;
	outgoingLink->nextOutgoingLink[5] = 0;
	
	Star_getNodeDestinations(star, outgoingLinkPlace, destinations, length);
	
	// first
	
	assert(
		0 == strcmp(outgoingLink->method[0], "Link_read") 
		&& outgoingLink->place[0] == outgoingLinkPlace
	);
	
	assert(0 == strcmp(outgoingLink->method[1], "Link_getOutgoingNode"));
	
	assert(0 == strcmp(outgoingLink->method[2], "Link_getNextOutgoing"));
	
	assert(0 == strcmp(starError->method[0], "StarError_forbidShortDestinationList"));
	
	// next
	
	assert(
		0 == strcmp(outgoingLink->method[3], "Link_read") 
		&& outgoingLink->place[3] == nextOutgoingLinkPlace
	);
	
	assert(0 == strcmp(outgoingLink->method[4], "Link_getOutgoingNode"));
	
	assert(0 == strcmp(outgoingLink->method[5], "Link_getNextOutgoing"));
	
	assert(0 == strcmp(starError->method[1], "StarError_forbidShortDestinationList"));
	
	// exit
	
	assert(0 == strcmp(starError->method[2], "StarError_forbidLongDestinationList"));
	
	assert(destinations[0] == destination);
	assert(destinations[1] == nextDestination);
	
	free(destinations);
	
	demolishTest();
}

void it_finds_origins()
{
	prepareTest();
	
	size_t incomingLinkPlace = 24;
	size_t nextIncomingLinkPlace = 120;
	size_t length = 2;
	size_t * origins = malloc(sizeof(size_t) * length);
	size_t origin = 36;
	size_t nextOrigin = 126;
	
	incomingLink->originNode[1] = origin;
	incomingLink->nextIncomingLink[2] = nextIncomingLinkPlace;
	incomingLink->originNode[4] = nextOrigin;
	incomingLink->nextIncomingLink[5] = 0;
	
	Star_getNodeOrigins(star, incomingLinkPlace, origins, length);
	
	// first
	
	assert(
		0 == strcmp(incomingLink->method[0], "Link_read") 
		&& incomingLink->place[0] == incomingLinkPlace
	);
	
	assert(0 == strcmp(incomingLink->method[1], "Link_getIncomingNode"));
	
	assert(0 == strcmp(incomingLink->method[2], "Link_getNextIncoming"));
	
	assert(0 == strcmp(starError->method[0], "StarError_forbidShortOriginList"));
	
	// next
	
	assert(
		0 == strcmp(incomingLink->method[3], "Link_read") 
		&& incomingLink->place[3] == nextIncomingLinkPlace
	);
	
	assert(0 == strcmp(incomingLink->method[4], "Link_getIncomingNode"));
	
	assert(0 == strcmp(incomingLink->method[5], "Link_getNextIncoming"));
	
	assert(0 == strcmp(starError->method[1], "StarError_forbidShortOriginList"));
	
	// exit
	
	assert(0 == strcmp(starError->method[2], "StarError_forbidLongOriginList"));
	
	assert(origins[0] == origin);
	assert(origins[1] == nextOrigin);
	
	free(origins);
	
	demolishTest();
}

void it_deletes_outgoing_link()
{
	prepareTest();
	
	size_t outgoingStartLink = 18;
	size_t destinationNode = 36;
	
	Star_deleteOutgoingLink(star, outgoingStartLink, destinationNode);
	
//	assert(
//		0 == strcmp(incomingLink->method[0], "Link_read") 
//		&& incomingLink->place[0] == nextIncomingLinkPlace
//	);
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_adds_incoming_links();
	it_adds_outgoing_links();
	it_finds_destinations();
	it_finds_origins();
	it_deletes_outgoing_link();

	return (EXIT_SUCCESS);
}
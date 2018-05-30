#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Telescope.c"
#include "../Link.c"

struct Telescope * telescope;
struct Link * link;

void prepareTest()
{
	link = Link_mock();
	
	telescope = Telescope_construct(link);
}

void demolishTest()
{
	Telescope_destruct(telescope);
}

void it_finds_incoming_link()
{
	prepareTest();
	
	size_t incomingLinkPlace = 24;
	size_t originNodePlace = 6;
	size_t nextIncomingLinkPlace = 42;
	
	incomingLink->isIncomingFromNode[1] = 0;
	incomingLink->nextIncomingLink[2] = nextIncomingLinkPlace;
	incomingLink->isIncomingFromNode[4] = 1;
	
	size_t result = Telescope_findIncomingLink(telescope, incomingLinkPlace, originNodePlace);
	
	assert(
		0 == strcmp(incomingLink->method[0], "Link_read") 
		&& incomingLink->place[0] == incomingLinkPlace
	);
	
	assert(
		0 == strcmp(incomingLink->method[1], "Link_isIncomingFromNode") 
		&& incomingLink->originNode[1] == originNodePlace
	);
	
	assert(0 == strcmp(incomingLink->method[2], "Link_getNextIncoming"));
	
	assert(
		0 == strcmp(incomingLink->method[3], "Link_read") 
		&& incomingLink->place[3] == nextIncomingLinkPlace
	);
	
	assert(
		0 == strcmp(incomingLink->method[4], "Link_isIncomingFromNode") 
		&& incomingLink->originNode[4] == originNodePlace
	);
	
	assert(result == nextIncomingLinkPlace);
	
	demolishTest();
}

void it_finds_no_incoming_link()
{
	prepareTest();
	
	size_t incomingLinkPlace = 24;
	size_t originNodePlace = 6;
	size_t nextIncomingLinkPlace = 42;
	
	incomingLink->isIncomingFromNode[1] = 0;
	incomingLink->nextIncomingLink[2] = nextIncomingLinkPlace;
	incomingLink->isIncomingFromNode[4] = 0;
	incomingLink->nextIncomingLink[5] = 0;
	
	size_t result = Telescope_findIncomingLink(telescope, incomingLinkPlace, originNodePlace);

	assert(
		0 == strcmp(incomingLink->method[0], "Link_read") 
		&& incomingLink->place[0] == incomingLinkPlace
	);

	assert(
		0 == strcmp(incomingLink->method[1], "Link_isIncomingFromNode") 
		&& incomingLink->originNode[1] == originNodePlace
	);
	
	assert(0 == strcmp(incomingLink->method[2], "Link_getNextIncoming"));
	
	assert(
		0 == strcmp(incomingLink->method[3], "Link_read") 
		&& incomingLink->place[3] == nextIncomingLinkPlace
	);

	assert(
		0 == strcmp(incomingLink->method[4], "Link_isIncomingFromNode") 
		&& incomingLink->originNode[4] == originNodePlace
	);
	
	assert(result == 0);
	
	demolishTest();
}

void it_finds_outgoing_link()
{
	prepareTest();
	
	size_t outgoingLinkPlace = 24;
	size_t destinationNodePlace = 6;
	size_t nextOutgoingLinkPlace = 42;
	
	outgoingLink->isOutgoingToNode[1] = 0;
	outgoingLink->nextOutgoingLink[2] = nextOutgoingLinkPlace;
	outgoingLink->isOutgoingToNode[4] = 1;
	
	size_t result = Telescope_findOutgoingLink(telescope, outgoingLinkPlace, destinationNodePlace);
	
	assert(
		0 == strcmp(outgoingLink->method[0], "Link_read") 
		&& outgoingLink->place[0] == outgoingLinkPlace
	);
	
	assert(
		0 == strcmp(outgoingLink->method[1], "Link_isOutgoingToNode") 
		&& outgoingLink->destinationNode[1] == destinationNodePlace
	);
	
	assert(0 == strcmp(outgoingLink->method[2], "Link_getNextOutgoing"));
	
	assert(
		0 == strcmp(outgoingLink->method[3], "Link_read") 
		&& outgoingLink->place[3] == nextOutgoingLinkPlace
	);
	
	assert(
		0 == strcmp(outgoingLink->method[4], "Link_isOutgoingToNode") 
		&& outgoingLink->destinationNode[4] == destinationNodePlace
	);
	
	assert(result == nextOutgoingLinkPlace);
	
	demolishTest();
}

void it_finds_no_outgoing_link()
{
	prepareTest();
	
	size_t outgoingLinkPlace = 24;
	size_t destinationNodePlace = 6;
	size_t nextOutgoingLinkPlace = 42;
	
	outgoingLink->isOutgoingToNode[1] = 0;
	outgoingLink->nextOutgoingLink[2] = nextOutgoingLinkPlace;
	outgoingLink->isOutgoingToNode[4] = 0;
	outgoingLink->nextOutgoingLink[5] = 0;
	
	size_t result = Telescope_findOutgoingLink(telescope, outgoingLinkPlace, destinationNodePlace);

	assert(
		0 == strcmp(outgoingLink->method[0], "Link_read") 
		&& outgoingLink->place[0] == outgoingLinkPlace
	);

	assert(
		0 == strcmp(outgoingLink->method[1], "Link_isOutgoingToNode") 
		&& outgoingLink->destinationNode[1] == destinationNodePlace
	);
	
	assert(0 == strcmp(outgoingLink->method[2], "Link_getNextOutgoing"));
	
	assert(
		0 == strcmp(outgoingLink->method[3], "Link_read") 
		&& outgoingLink->place[3] == nextOutgoingLinkPlace
	);

	assert(
		0 == strcmp(outgoingLink->method[4], "Link_isOutgoingToNode") 
		&& outgoingLink->destinationNode[4] == destinationNodePlace
	);
	
	assert(result == 0);
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_finds_incoming_link();
	it_finds_no_incoming_link();
	it_finds_outgoing_link();
	it_finds_no_outgoing_link();

	return (EXIT_SUCCESS);
}
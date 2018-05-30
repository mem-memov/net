#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Star.c"
#include "../Link.c"

struct Star * star;
struct Link * incomingLink;
struct Link * outgoingLink;

void prepareTest()
{
	incomingLink = Link_mock();
	outgoingLink = Link_mock();
	
	star = Star_construct(incomingLink, outgoingLink);
}

void demolishTest()
{
	Star_destruct(star);
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

void it_finds_incoming_link()
{
	prepareTest();
	
	size_t incomingLinkPlace = 24;
	size_t originNodePlace = 6;
	size_t nextIncomingLinkPlace = 42;
	
	incomingLink->isIncomingFromNode[1] = 0;
	incomingLink->nextIncomingLink[2] = nextIncomingLinkPlace;
	incomingLink->isIncomingFromNode[4] = 1;
	
	size_t result = Star_findIncomingLink(star, incomingLinkPlace, originNodePlace);
	
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
	
	size_t result = Star_findIncomingLink(star, incomingLinkPlace, originNodePlace);

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

int main(int argc, char** argv)
{
	it_adds_incoming_links();
	it_adds_outgoing_links();
	//it_finds_incoming_link();
	it_finds_no_incoming_link();

	return (EXIT_SUCCESS);
}
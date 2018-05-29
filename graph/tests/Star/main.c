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

int main(int argc, char** argv)
{
	it_adds_incoming_links();
	it_adds_outgoing_links();

	return (EXIT_SUCCESS);
}
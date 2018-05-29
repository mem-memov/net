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

int main(int argc, char** argv)
{
	

	return (EXIT_SUCCESS);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Link.c"
#include "Direction.c"

struct Link * link;
struct Direction * outgoing;
struct Direction * incoming;

void prepareTest(size_t * places)
{
	struct Direction * outgoing = malloc(sizeof(struct Direction));
	struct Direction * incoming = malloc(sizeof(struct Direction));
	link = Link_construct(places, outgoing, incoming);
}

void demolishTest()
{
	Link_destruct(link);
}

int main(int argc, char** argv)
{


	return (EXIT_SUCCESS);
}


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
	outgoing = malloc(sizeof(struct Direction));
	incoming = malloc(sizeof(struct Direction));
	link = Link_construct(places, outgoing, incoming);
}

void demolishTest()
{
	Link_destruct(link);
}

void test_it_provides_its_place_in_store()
{
	
}

void test_it_writes_new_link_to_store()
{
    // 6 -> 12
	//                 0             6              12              18 
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	//                               ^ node         ^ node          ^ link
	prepareTest(places);
	
	size_t place = 18;
	size_t origin = 6;
	size_t destination = 12;
	Link_create(link, place, origin, destination);
	
	assert(place == link->place && "A new link keeps its place in the store.");

	assert(0 == strcmp(outgoing->method, "Direction_create"));
	assert(place == outgoing->place && "Direction_create place");
	assert(destination == outgoing->destination && "Direction_create destination");
	
	assert(0 == strcmp(incoming->method, "Direction_create"));
	assert(place == incoming->place && "Direction_create place");
	assert(origin == incoming->destination && "Direction_create destination");
	
	demolishTest();
}

int main(int argc, char** argv)
{
	test_it_provides_its_place_in_store();
	test_it_writes_new_link_to_store();

	return (EXIT_SUCCESS);
}


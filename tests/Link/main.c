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
    // 6 -> 12
	//                 0             6              12              18 
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	//                               ^ node         ^ node          ^ link
	prepareTest(places);

	size_t place = 18;
	link->place = place;
	size_t result = Link_getPlace(link);
	
	assert(result == place && "A new link supplies its place in the store when requested.");
	
	demolishTest();
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

void test_it_reads_link_fields_from_store()
{
    // 6 -> 12
	//                 0             6              12              18 
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	//                               ^ node         ^ node          ^ link
	prepareTest(places);
	
	size_t place = 18;
	Link_read(link, place);
	
	assert(place == link->place && "An existing link keeps its place in the store.");

	assert(0 == strcmp(outgoing->method, "Direction_read"));
	assert(place == outgoing->place && "Direction_read place");
	
	assert(0 == strcmp(incoming->method, "Direction_read"));
	assert(place == incoming->place && "Direction_read place");
	
	demolishTest();
}

void test_it_joins_chain_of_outgoing_directions()
{
    // 6 -> 12
    // 6 -> 18
	//                 0             6              12              18               24               30
	size_t places[] = {0,0,0,0,0,0,  6,0,2,0,24,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,30,0,6,12,0,  18,0,0,6,0,0};
	//                               ^ node         ^ node           ^ node          ^ link            ^ new link
	prepareTest(places);
	
	size_t place = 30;
	Link_read(link, place);
	
	size_t previous = 6;
	size_t next = 24;
	Link_joinOutgoing(link, previous, next);
	
	assert(0 == strcmp(outgoing->method, "Direction_joinChain"));
	assert(previous == outgoing->previous && "Direction_joinChain previous");
	assert(next == outgoing->next && "Direction_joinChain next");
	
	demolishTest();
}

void test_it_joins_chain_of_incoming_directions()
{
    // 6 -> 12
    // 6 -> 18
	//                 0             6              12              18               24               30
	size_t places[] = {0,0,0,0,0,0,  6,0,2,0,24,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,30,0,6,12,0,  18,0,0,6,0,0};
	//                               ^ node         ^ node           ^ node          ^ link            ^ new link
	prepareTest(places);
	
	size_t place = 30;
	Link_read(link, place);
	
	size_t previous = 18;
	size_t next = 0;
	Link_joinIncoming(link, previous, next);
	
	assert(0 == strcmp(incoming->method, "Direction_joinChain"));
	assert(previous == incoming->previous && "Direction_joinChain previous");
	assert(next == incoming->next && "Direction_joinChain next");
	
	demolishTest();
}

void test_it_gets_shifted_back_in_outgoing_chain()
{
    // 6 -> 12
    // 6 -> 18
	//                 0             6              12              18               24 +             30
	size_t places[] = {0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,30,0,6,12,0,  18,6,24,6,18,0};
	//                               ^ node         ^ node           ^ node          ^ shifted link   ^ new link
	prepareTest(places);
	
	size_t place = 24;
	Link_read(link, place);
	
	size_t previous = 30;
	Link_shiftOutgoing(link, previous);
	
	assert(0 == strcmp(outgoing->method, "Direction_append"));
	assert(previous == outgoing->previous && "Direction_append previous");
	
	demolishTest();
}

void test_it_gets_shifted_back_in_incoming_chain()
{
    // 6 -> 12
	//                 0             6              12              18               24         +
	size_t places[] = {0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,30,0,6,12,0};
	//                               ^ node         ^ node           ^ node          ^ shifted link
	prepareTest(places);
	
	size_t place = 24;
	Link_read(link, place);
	
	size_t previous = 12;
	Link_shiftIncoming(link, previous);
	
	assert(0 == strcmp(incoming->method, "Direction_append"));
	assert(previous == incoming->previous && "Direction_append previous");
	
	demolishTest();
}

int main(int argc, char** argv)
{
	test_it_provides_its_place_in_store();
	test_it_writes_new_link_to_store();
	test_it_reads_link_fields_from_store();
	test_it_joins_chain_of_outgoing_directions();
	test_it_joins_chain_of_incoming_directions();
	test_it_gets_shifted_back_in_outgoing_chain();
	test_it_gets_shifted_back_in_incoming_chain();

	return (EXIT_SUCCESS);
}


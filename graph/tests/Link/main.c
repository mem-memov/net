#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Link.c"
#include "../Direction.c"
#include "../LinkError.c"

struct Link * link;
struct LinkError * error;
struct Direction * outgoing;
struct Direction * incoming;

void prepareTest()
{
	outgoing = Direction_mock();
	incoming = Direction_mock();
	error = LinkError_mock();
	link = Link_construct(outgoing, incoming, error);
}

void demolishTest()
{
	Link_destruct(link);
	LinkError_destruct(error);
}

void it_provides_its_place_in_store()
{
	// 0             6  node        12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0

	prepareTest();

	size_t place = 18;
	link->place = place;
	
	size_t result = Link_getPlace(link);
	
	assert(result == place && "A new link supplies its place in the store when requested.");
	
	demolishTest();
}

void it_writes_new_link_to_store()
{
	// 0             6  node        12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,0,0,0,0,   12,0,0,0,0,0,   0,0,0,0,0,0
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0

	prepareTest();
	
	size_t place = 18;
	size_t origin = 6;
	size_t destination = 12;
	
	Link_create(link, place, origin, destination);
	
	assert(
		0 == strcmp(error->method[0], "LinkError_forbidSelfPointingNodes")
		&& error->origin[0] == origin
		&& error->destination[0] == destination
	);
	
	assert(place == link->place && "A new link keeps its place in the store.");

	assert(
		0 == strcmp(outgoing->method[0], "Direction_create")
		&& outgoing->place[0] == place
		&& outgoing->destination[0] == destination
	);
	
	assert(
		0 == strcmp(incoming->method[0], "Direction_create")
		&& incoming->place[0] == place
		&& incoming->destination[0] == origin
	);

	demolishTest();
}

void it_reads_link_fields_from_store()
{
	// 0             6  node        12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,0,0,0,0,   12,0,0,0,0,0,   0,0,0,0,0,0
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0

	prepareTest();
	
	size_t place = 18;
	
	Link_read(link, place);
	
	assert(place == link->place && "An existing link keeps its place in the store.");

	assert(
		0 == strcmp(outgoing->method[0], "Direction_read")
		&& outgoing->place[0] == place
	);
	
	assert(
		0 == strcmp(incoming->method[0], "Direction_read")
		&& incoming->place[0] == place
	);
	
	demolishTest();
}

void it_joins_chain_of_outgoing_directions()
{
	// 0             6 node         12 node         18 node          24 6->12         30 6->18
	// 0,0,0,0,0,0,  6,0,1,0,24,0,  12,0,0,1,0,24,  18,0,0,0,0,0,    12,6,0,6,12,0,   0,0,0,0,0,0
	// 0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,30,0,6,12,0,  18,6,24,6,18,0
	//                                                                                   ^ ^
	prepareTest();

	size_t previous = 6;
	size_t next = 24;
	
	Link_joinOutgoing(link, previous, next);
	
	assert(
		0 == strcmp(outgoing->method[0], "Direction_joinChain")
		&& outgoing->previous[0] == previous
		&& outgoing->next[0] == next
	);
	
	demolishTest();
}

void it_joins_chain_of_incoming_directions()
{
	// 0             6 node         12 node         18 node          24 6->12         30 6->18
	// 0,0,0,0,0,0,  6,0,1,0,24,0,  12,0,0,1,0,24,  18,0,0,0,0,0,    12,6,0,6,12,0,   0,0,0,0,0,0
	// 0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,30,0,6,12,0,  18,6,24,6,18,0
	//                                                                                           ^ ^
	prepareTest();

	size_t previous = 18;
	size_t next = 0;
	
	Link_joinIncoming(link, previous, next);
	
	assert(
		0 == strcmp(incoming->method[0], "Direction_joinChain")
		&& incoming->previous[0] == previous
		&& incoming->next[0] == next
	);
	
	demolishTest();
}

void it_gets_shifted_back_in_outgoing_chain()
{
	// 0             6 node         12 node         18 node          24 6->12         30 6->18
	// 0,0,0,0,0,0,  6,0,1,0,24,0,  12,0,0,1,0,24,  18,0,0,0,0,0,    12,6,0,6,12,0,   0,0,0,0,0,0
	// 0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,30,0,6,12,0,  18,6,24,6,18,0
	//                                                                  ^
	prepareTest();

	size_t previous = 30;
	
	Link_shiftOutgoing(link, previous);
	
	assert(
		0 == strcmp(outgoing->method[0], "Direction_append")
		&& outgoing->previous[0] == previous 
	);
	
	demolishTest();
}

void it_gets_shifted_back_in_incoming_chain()
{
	// 0             6 node         12 node         18 node          24 6->12        30 18->12
	// 0,0,0,0,0,0,  6,0,1,0,24,0,  12,0,0,1,0,24,  18,0,0,0,0,0,    12,6,0,6,12,0,  0,0,0,0,0,0
	// 0,0,0,0,0,0,  6,0,1,0,24,0,  12,0,0,2,0,30,  18,0,0,1,0,30,   12,6,0,6,30,0,  12,18,0,18,12,24
	//                                                                        ^
	prepareTest();

	size_t previous = 30;
	
	Link_shiftIncoming(link, previous);
	
	assert(
		0 == strcmp(incoming->method[0], "Direction_append")
		&& incoming->previous[0] == previous
	);
	
	demolishTest();
}

void it_confirms_connection_to_outgoing_node()
{
	// 0             6  node        12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	
	prepareTest();

	size_t destination = 12;
	outgoing->result[0] = 1;
	
	size_t result = Link_isOutgoingToNode(link, destination);
	
	assert(
		0 == strcmp(outgoing->method[0], "Direction_hasNode")
		&& outgoing->node[0] == destination
	);
	
	assert(result == 1 && "node present");
	
	demolishTest();
}

void it_denies_connection_to_outgoing_node()
{
	// 0             6  node        12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	
	prepareTest();

	size_t destination = 36;
	outgoing->result[0] = 0;
	
	size_t result = Link_isOutgoingToNode(link, destination);
	
	assert(
		0 == strcmp(outgoing->method[0], "Direction_hasNode")
		&& outgoing->node[0] == destination
	);
	
	assert(result == 0 && "node absent");
	
	demolishTest();
}

void it_confirms_connection_to_incoming_node()
{
	// 0             6  node        12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	
	prepareTest();

	size_t origin = 6;
	incoming->result[0] = 1;
	size_t result = Link_isIncomingFromNode(link, origin);
	
	assert(
		0 == strcmp(incoming->method[0], "Direction_hasNode")
		&& incoming->node[0] == origin
	);

	assert(result == 1 && "node present");
	
	demolishTest();
}

void it_denies_connection_to_incoming_node()
{
	// 0             6  node        12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	
	prepareTest();

	size_t origin = 36;
	incoming->result[0] = 0;
	
	size_t result = Link_isIncomingFromNode(link, origin);
	
	assert(0 == strcmp(
		incoming->method[0], "Direction_hasNode")
		&& incoming->node[0] == origin
	);
	
	assert(result == 0 && "node absent");
	
	demolishTest();
}

void it_supplies_next_outgoing_direction()
{
	// 0             6              12              18               24 6->12         30 6->18
	// 0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,30,0,6,12,0,  18,6,24,6,18,0
	//                                                                                     ^
	prepareTest();

	outgoing->result[0] = 24;
	
	size_t result = Link_getNextOutgoing(link);
	
	assert(0 == strcmp(outgoing->method[0], "Direction_getNext"));
	
	assert(result == 24 && "next outgoing entry");
	
	demolishTest();
}

void it_supplies_next_incoming_direction()
{
	// 0             6 node         12 node         18 node          24 6->12        30 18->12
	// 0,0,0,0,0,0,  6,0,1,0,24,0,  12,0,0,2,0,30,  18,0,0,1,0,30,   12,6,0,6,30,0,  12,18,0,18,12,24
	//                                                                        ^
	prepareTest();

	incoming->result[0] = 24;
	
	size_t result = Link_getNextIncoming(link);
	
	assert(0 == strcmp(incoming->method[0], "Direction_getNext"));
	
	assert(result == 24 && "next incoming entry");
	
	demolishTest();
}

void it_deletes_link()
{
	// 0             6  node        12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	// 0,0,0,0,0,0,  6,0,0,0,0,0,   12,0,0,0,0,0,   0,0,0,0,0,0
	
	prepareTest();

	Link_delete(link);
	
	assert(0 == strcmp(outgoing->method[0], "Direction_delete"));
	assert(0 == strcmp(incoming->method[0], "Direction_delete"));
	
	demolishTest();
}

void it_supplies_outgoing_node()
{
	// 0             6  node        12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	//                                              ^
	prepareTest();

	outgoing->result[0] = 12;
	
	size_t result = Link_getOutgoingNode(link);
	
	assert(0 == strcmp(outgoing->method[0], "Direction_getNode"));
	
	assert(result == 12 && "the node this link points to");
	
	demolishTest();
}

void it_supplies_incoming_node()
{
	// 0             6  node        12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	//                                                     ^
	prepareTest();

	incoming->result[0] = 6;
	
	size_t result = Link_getIncomingNode(link);
	
	assert(0 == strcmp(incoming->method[0], "Direction_getNode"));
	
	assert(result == 6 && "the node this link points from");
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_provides_its_place_in_store();
	it_writes_new_link_to_store();
	it_reads_link_fields_from_store();
	it_joins_chain_of_outgoing_directions();
	it_joins_chain_of_incoming_directions();
	it_gets_shifted_back_in_outgoing_chain();
	it_gets_shifted_back_in_incoming_chain();
	it_confirms_connection_to_outgoing_node();
	it_denies_connection_to_outgoing_node();
	it_confirms_connection_to_incoming_node();
	it_denies_connection_to_incoming_node();
	it_supplies_next_outgoing_direction();
	it_supplies_next_incoming_direction();
	it_deletes_link();
	it_supplies_outgoing_node();
	it_supplies_incoming_node();

	return (EXIT_SUCCESS);
}


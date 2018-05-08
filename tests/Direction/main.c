#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Direction.c"
#include "DirectionError.c"
#include "Place.c"

struct DirectionError * nextOutgoingError;
struct Direction * nextOutgoing;
struct DirectionError * outgoingError;
struct Place * outgoingNode;
struct Place * outgoingPrevious;
struct Place * outgoingNext;
struct Direction * outgoing;

struct DirectionError * nextIncomingError;
struct Direction * nextIncoming;
struct DirectionError * incomingError;
struct Place * incomingNode;
struct Place * incomingPrevious;
struct Place * incomingNext;
struct Direction * incoming;


void prepareTest()
{
	nextOutgoingError = DirectionError_mock();
	nextOutgoing = Direction_constructOutgoing(nextOutgoingError, Place_mock(), Place_mock(), Place_mock());
	outgoingError = DirectionError_mock();
	outgoingNode = Place_mock();
	outgoingPrevious = Place_mock();
	outgoingNext = Place_mock();
	outgoing = Direction_constructOutgoing(outgoingError, outgoingNode, outgoingPrevious, outgoingNext);
	Direction_setPool(outgoing, nextOutgoing);

	nextIncomingError = DirectionError_mock();
	nextIncoming = Direction_constructIncoming(nextIncomingError, Place_mock(), Place_mock(), Place_mock());
	incomingError = DirectionError_mock();
	incomingNode = Place_mock();
	incomingPrevious = Place_mock();
	incomingNext = Place_mock();
	incoming = Direction_constructIncoming(incomingError, incomingNode, incomingPrevious, incomingNext);
	Direction_setPool(incoming, nextIncoming);
}

void demolishTest()
{
	Direction_destruct(outgoing);
	DirectionError_destruct(outgoingError);
	DirectionError_destruct(nextOutgoingError);
	
	Direction_destruct(incoming);
	DirectionError_destruct(incomingError);
	DirectionError_destruct(nextIncomingError);
}

void it_contructs_an_outgoing_direction()
{
	prepareTest();
	
	assert(outgoing->offset == 0 && "An outgoing direction starts at the beginning of an entry.");
	
	demolishTest();
}

void it_contructs_an_incoming_direction()
{
	prepareTest();

	assert(incoming->offset == 3 && "An incoming direction starts right after the outgoing direction.");
	
	demolishTest();
}

void it_supplies_its_place_inside_the_storage_array()
{
	prepareTest();
	
	size_t place = 18;
	Direction_read(outgoing, place);
	
	size_t result = Direction_getPlace(outgoing);
	
	assert(result == place && "A direction keeps the place it is bound to inside the storage array.");
	
	demolishTest();
}

void it_writes_values_of_a_fresh_direction_to_the_store()
{
	// 0             6 node         12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,0,0,0,0,   12,0,0,0,0,0,   0,0,0,0,0,0
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	//                                              ^  ^ ^
	prepareTest();
	
	size_t place = 18;
	size_t destination = 12;
	Direction_create(outgoing, place, destination);
	
	// bind
	assert(outgoing->place == place && "A direction keeps the place it is bound to inside the storage array.");
	assert(
		0 == strcmp(outgoing->node->method[0], "Place_bind") 
		&& outgoing->node->position[0] == 18
		&& "A direction keeps the node it points to."
	);
	assert(
		0 == strcmp(outgoing->previous->method[0], "Place_bind") 
		&& outgoing->previous->position[0] == 19
		&& "A direction can be connected to a previous direction."
	);
	assert(
		0 == strcmp(outgoing->next->method[0], "Place_bind") 
		&& outgoing->next->position[0] == 20
		&& "A new direction can be connected to a following direction."
	);
	
	// create
	assert(
		0 == strcmp(outgoing->node->method[1], "Place_set") 
		&& outgoing->node->value[1] == destination 
		&& "A direction keeps the node it points to."
	);
	assert(
		0 == strcmp(outgoing->previous->method[1], "Place_set") 
		&& outgoing->previous->value[1] == 0 
		&& "A new direction is not connected to any previous direction."
	);
	assert(
		0 == strcmp(outgoing->next->method[1], "Place_set") 
		&& outgoing->next->value[1] == 0 
		&& "A new direction is not connected to any following direction."
	);

	demolishTest();
}

void it_reads_values_of_an_existing_direction_from_the_store()
{
	// 0             6 node         12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	//                                              ^  ^ ^
	prepareTest();
	
	size_t place = 18;
	Direction_read(outgoing, place);
	
	// bind
	assert(outgoing->place == place && "A direction keeps the place it is bound to inside the storage array.");
	assert(
		0 == strcmp(outgoing->node->method[0], "Place_bind") 
		&& outgoing->node->position[0] == 18
		&& "A direction keeps the node it points to."
	);
	assert(
		0 == strcmp(outgoing->previous->method[0], "Place_bind") 
		&& outgoing->previous->position[0] == 19
		&& "A direction can be connected to a previous direction."
	);
	assert(
		0 == strcmp(outgoing->next->method[0], "Place_bind") 
		&& outgoing->next->position[0] == 20
		&& "A new direction can be connected to a following direction."
	);

	demolishTest();
}

void it_joins_chain_of_directions()
{
	// 0             6 node         12 node         18 node          24 6->12         30 6->18
	// 0,0,0,0,0,0,  6,0,1,0,24,0,  12,0,0,1,0,24,  18,0,0,0,0,0,    12,6,0,6,12,0,   0,0,0,0,0,0
	// 0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,6,0,6,12,0,   18,6,24,6,18,0
	//                                                                                   ^  ^
	prepareTest();
	
	size_t previousPlace = 6;
	size_t nextPlace = 24;

	Direction_joinChain(outgoing, previousPlace, nextPlace);
	
	assert(
		0 == strcmp(outgoingError->method, "DirectionError_forbidZeroAndEqualtyForPreviousAndNext") 
		&& outgoingError->previous == previousPlace
		&& outgoingError->next == nextPlace
	);
	assert(
		0 == strcmp(outgoing->previous->method[0], "Place_set") 
		&& outgoing->previous->value[0] == previousPlace
		&& "A direction gets connected to a previous entry (a node)."
	);
	assert(
		0 == strcmp(outgoing->next->method[0], "Place_set") 
		&& outgoing->next->value[0] == nextPlace
		&& "A new direction gets connected to a following direction."
	);

	demolishTest();
}

void it_gets_appended_to_a_previous_direction()
{
	// 0             6 node         12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,0,0,0,0,   12,0,0,0,0,0,   0,0,0,0,0,0
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	//                                                 ^
	prepareTest();

	size_t previousPlace = 6;
	Direction_append(outgoing, previousPlace);
	
	assert(
		0 == strcmp(outgoingError->method, "DirectionError_forbidZeroPlaceForPrevious") 
		&& outgoingError->previous == previousPlace
	);
	
	assert(
		0 == strcmp(outgoing->previous->method[0], "Place_set") 
		&& outgoing->previous->value[0] == previousPlace
		&& "A direction gets connected to a previous entry (a node)."
	);

	demolishTest();
}

void it_confirms_directing_to_a_particular_node()
{
	// 0             6 node         12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	//                                              ^
	prepareTest();

	size_t nodePlace = 12;
	outgoing->node->value[0] = nodePlace;
	size_t result = Direction_hasNode(outgoing, nodePlace);
	
	assert(
		0 == strcmp(outgoing->node->method[0], "Place_get") 
		&& result == 1
		&& "A direction confirms it points to a particular node."
	);
	
	demolishTest();
}

void it_denies_directing_to_a_particular_node()
{
	// 0             6 node         12 node         18 6->12        24
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0,  24,0,0,0,0,0
	//                                              ^
	prepareTest();

	size_t nodePlace = 24;
	outgoing->node->value[0] = 12;
	size_t result = Direction_hasNode(outgoing, nodePlace);
	
	assert(
		0 == strcmp(outgoing->node->method[0], "Place_get") 
		&& result == 0
		&& "A direction denies it points to a particular node."
	);

	demolishTest();
}

void it_supplies_the_node_it_directs_to()
{
	// 0             6 node         12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	//                                              ^
	prepareTest();

	outgoing->node->value[0] = 12;
	size_t result = Direction_getNode(outgoing);
	
	assert(
		0 == strcmp(outgoing->node->method[0], "Place_get") 
		&& result == 12
		&& "A direction supplies the place a node occupies that it points to."
	);
	
	demolishTest();
}

void it_supplies_the_place_of_the_next_direction()
{
	// 0             6 node         12 node         18 node          24 6->12        30 6->18
	// 0,0,0,0,0,0,  6,0,2,0,24,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,6,0,6,12,0,  18,6,24,6,18,0
	//                                                                                    ^
	prepareTest();

	size_t nextPlace = 24;
	outgoing->next->value[0] = nextPlace;
	size_t result = Direction_getNext(outgoing);
	
	assert(
		0 == strcmp(outgoing->next->method[0], "Place_get") 
		&& result == nextPlace
		&& "A direction supplies the place of the next direction in the chain."
	);

	demolishTest();
}

void it_gets_deleted_with_reconnection()
{
	// 0             6 node         12 node         18 node          24 6->12         30 6->18
	// 0,0,0,0,0,0,  6,0,2,0,24,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,30,0,6,12,0,  18,6,24,6,18,0
	// 0,0,0,0,0,0,  6,0,2,0,24,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,6,0,6,12,0,   0,0,0,6,18,0
	//                                                                  ^             ^ ^ ^
	prepareTest();

	size_t previousPlace = 6;
	size_t nextPlace = 24;
	outgoing->previous->value[0] = previousPlace;
	outgoing->next->value[0] = nextPlace;
	Direction_delete(outgoing);
	
	assert(0 == strcmp(outgoing->previous->method[0], "Place_get"));
	assert(0 == strcmp(outgoing->next->method[0], "Place_get"));

	assert(
		0 == strcmp(outgoingError->method, "DirectionError_forbidZeroPlaceForPrevious") 
		&& outgoingError->previous == previousPlace
	);

	// next bind
	assert(nextOutgoing->place == nextPlace && "The next direction keeps the place it is bound to inside the storage array.");
	assert(
		0 == strcmp(nextOutgoing->node->method[0], "Place_bind") 
		&& nextOutgoing->node->position[0] == 24
		&& "The next direction keeps the node it points to."
	);
	assert(
		0 == strcmp(nextOutgoing->previous->method[0], "Place_bind") 
		&& nextOutgoing->previous->position[0] == 25
		&& "The next direction can be connected to a previous direction."
	);
	assert(
		0 == strcmp(nextOutgoing->next->method[0], "Place_bind") 
		&& nextOutgoing->next->position[0] == 26
		&& "The next new direction can be connected to a following direction."
	);
	
	// next append
	assert(
		0 == strcmp(nextOutgoing->previous->method[1], "Place_set") 
		&& nextOutgoing->previous->value[1] == previousPlace
		&& "Direction_append The previous direction gets reconnected."
	);
	
	assert(
		0 == strcmp(outgoing->node->method[0], "Place_set") 
		&& outgoing->node->value[0] == 0
		&& "All fields of a deleted direction are set to zero."
	);
	assert(
		0 == strcmp(outgoing->previous->method[1], "Place_set") 
		&& outgoing->previous->value[1] == 0
		&& "All fields of a deleted direction are set to zero."
	);
	assert(
		0 == strcmp(outgoing->next->method[1], "Place_set") 
		&& outgoing->next->value[1] == 0
		&& "All fields of a deleted direction are set to zero."
	);
	
	demolishTest();
}

void it_gets_deleted_without_reconnection()
{
	// 0             6 node         12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	//                                              
	prepareTest();

	size_t previousPlace = 6;
	size_t nextPlace = 0;
	outgoing->previous->value[0] = previousPlace;
	outgoing->next->value[0] = nextPlace;
	Direction_delete(outgoing);
	
	assert(0 == strcmp(outgoing->previous->method[0], "Place_get"));
	assert(0 == strcmp(outgoing->next->method[0], "Place_get"));
	
	// next bind
	assert(0 == strcmp(nextOutgoing->node->method[0], "method not specified"));
	assert(0 == strcmp(nextOutgoing->previous->method[0], "method not specified"));
	assert(0 == strcmp(nextOutgoing->next->method[0], "method not specified"));
	
	// next append
	assert(0 == strcmp(nextOutgoing->previous->method[1], "method not specified"));
	
	assert(
		0 == strcmp(outgoing->node->method[0], "Place_set") 
		&& outgoing->node->value[0] == 0
		&& "All fields of a deleted direction are set to zero."
	);
	assert(
		0 == strcmp(outgoing->previous->method[1], "Place_set") 
		&& outgoing->previous->value[1] == 0
		&& "All fields of a deleted direction are set to zero."
	);
	assert(
		0 == strcmp(outgoing->next->method[1], "Place_set") 
		&& outgoing->next->value[1] == 0
		&& "All fields of a deleted direction are set to zero."
	);
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_contructs_an_outgoing_direction();
	it_contructs_an_incoming_direction();
	it_supplies_its_place_inside_the_storage_array();
	it_writes_values_of_a_fresh_direction_to_the_store();
	it_reads_values_of_an_existing_direction_from_the_store();
	it_joins_chain_of_directions();
	it_gets_appended_to_a_previous_direction();
	it_confirms_directing_to_a_particular_node();
	it_denies_directing_to_a_particular_node();
	it_supplies_the_node_it_directs_to();
	it_supplies_the_place_of_the_next_direction();
	it_gets_deleted_with_reconnection();
	it_gets_deleted_without_reconnection();

	return (EXIT_SUCCESS);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Direction.c"
#include "DirectionError.c"

struct DirectionError * error;
struct Direction * outgoing;
struct Direction * nextOutgoing;
struct Direction * incoming;
struct Direction * nextIncoming;

void prepareTest(size_t * places)
{
	error = DirectionError_mock();
	outgoing = Direction_constructOutgoing(places, error);
	nextOutgoing = Direction_constructOutgoing(places, error);
	incoming = Direction_constructIncoming(places, error);
	nextIncoming = Direction_constructIncoming(places, error);
}

void demolishTest()
{
	Direction_destruct(outgoing);
	Direction_destruct(nextOutgoing);
	Direction_destruct(incoming);
	Direction_destruct(nextIncoming);
	DirectionError_destruct(error);
}

void it_contructs_an_outgoing_direction()
{
    // 6 -> 12
	//                 0             6              12              18
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	//                                                               ^ outgoing
	prepareTest(places);
	
	assert(outgoing->places == places && "A direction can access data in this store.");
	assert(outgoing->offset == 0 && "An outgoing direction starts at the beginning of an entry.");
	assert(outgoing->nextDirection == NULL && "A new direction is not connected to any other direction.");
	
	demolishTest();
}

void it_contructs_an_incoming_direction()
{
    // 6 -> 12
	//                 0             6              12              18
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	//                                                                     ^ incoming
	prepareTest(places);
	
	assert(incoming->places == places && "A direction can access data in this store.");
	assert(incoming->offset == 3 && "An incoming direction starts right after the outgoing direction.");
	assert(incoming->nextDirection == NULL && "A new direction is not connected to any other direction.");
	
	demolishTest();
}

void it_accepts_help_structures_to_avoid_eternal_cycle_when_constructing()
{
    // 6 -> 12
	//                 0             6              12              18
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	                                                              
	prepareTest(places);

	Direction_setPool(outgoing, nextOutgoing);
	
	assert(outgoing->nextDirection == nextOutgoing && "A direction requires a helping set of pointers to operate on the next direction.");
	
	demolishTest();
}

void it_supplies_its_place_inside_the_storage_array()
{
    // 6 -> 12
	//                 0             6              12              18
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	//                                                               ^ outgoing
	prepareTest(places);
	
	size_t place = 18;
	Direction_read(outgoing, place);
	
	size_t result = Direction_getPlace(outgoing);
	
	assert(result == place && "A direction keeps the place it is bound to inside the storage array.");
	
	demolishTest();
}

void it_writes_values_of_a_fresh_direction_to_the_store()
{
    // 6 -> 12
	//                 0             6              12              18
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  7,7,7,7,7,7};
	//                                                               ^ outgoing
	prepareTest(places);
	
	size_t place = 18;
	size_t destination = 12;
	Direction_create(outgoing, place, destination);
	
	assert((*outgoing->node) == destination && places[18] == destination && "A direction keeps the node it points to.");
	assert((*outgoing->previous) == 0 && places[19] == 0 && "A new direction is not connected to any previous direction.");
	assert((*outgoing->next) == 0 && places[20] == 0 && "A new direction is not connected to any following direction.");
	
	demolishTest();
}

void it_reads_values_of_an_existing_direction_from_the_store()
{
    // 6 -> 12
	//                 0             6              12              18
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	//                                                               ^ outgoing
	
	prepareTest(places);
	
	size_t place = 18;
	Direction_read(outgoing, place);
	
	assert(outgoing->place == place && "A direction keeps the place it is bound to inside the storage array.");
	assert((*outgoing->node) == 12 && "A direction keeps the node it points to.");
	assert((*outgoing->previous) == 6 && "A direction can be connected to a previous direction.");
	assert((*outgoing->next) == 0 && "A new direction can be connected to a following direction.");
	
	demolishTest();
}

void it_joins_chain_of_directions()
{
    // 6 -> 12
    // 6 -> 18
	//                 0             6              12              18               24               30
	size_t places[] = {0,0,0,0,0,0,  6,0,2,0,24,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,6,30,6,12,0,  18,0,0,0,0,0};
	//                               ^ previous                                       ^ next           ^ new
	size_t previousPlace = 6;
	
	prepareTest(places);
	
	size_t place = 30;
	Direction_read(outgoing, place);

	size_t nextPlace = 24;
	Direction_read(nextOutgoing, nextPlace);
	
	Direction_joinChain(outgoing, previousPlace, nextPlace);

	assert((*outgoing->previous) == previousPlace && places[31] == previousPlace && "A direction gets connected to a previous entry (a node).");
	assert((*outgoing->next) == nextPlace && places[32] == nextPlace && "A new direction gets connected to a following direction.");
	
	demolishTest();
}

void it_gets_appended_to_a_previous_direction()
{
	//                 0             6              12              18
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  0,0,0,0,0,0};
	//                                                              ^ outgoing
	
	prepareTest(places);
	
	size_t place = 18;
	Direction_read(outgoing, place);
	
	size_t previousPlace = 6;
	Direction_append(outgoing, previousPlace);
	
	assert((*outgoing->previous) == previousPlace && places[19] == previousPlace && "A direction gets connected to a previous entry (a node).");
	
	demolishTest();
}

void it_confirms_directing_to_a_particular_node()
{
    // 6 -> 12
	//                 0             6              12              18
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	//                                                               ^ outgoing
	
	prepareTest(places);
	
	size_t place = 18;
	Direction_read(outgoing, place);
	
	size_t nodePlace = 12;
	size_t result = Direction_hasNode(outgoing, nodePlace);
	
	assert(result == 1 && "A direction confirms it points to a particular node.");
	
	demolishTest();
}

void it_denies_directing_to_a_particular_node()
{
    // 6 -> 12
	//                 0             6              12              18              24
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0,  24,0,0,0,0,0};
	//                                                               ^ outgoing     ^ some node
	
	prepareTest(places);
	
	size_t place = 18;
	Direction_read(outgoing, place);
	
	size_t nodePlace = 24;
	size_t result = Direction_hasNode(outgoing, nodePlace);
	
	assert(result == 0 && "A direction denies it points to a particular node.");
	
	demolishTest();
}

void it_supplies_the_node_it_directs_to()
{
    // 6 -> 12
	//                 0             6              12              18
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	//                                                               ^ outgoing
	
	prepareTest(places);
	
	size_t place = 18;
	Direction_read(outgoing, place);

	size_t result = Direction_getNode(outgoing);
	
	assert(result == 12 && result == places[18] && "A direction supplies the place a node occupies that it points to.");
	
	demolishTest();
}

void it_supplies_the_place_of_the_next_direction()
{
    // 6 -> 12
    // 6 -> 18
	size_t places[] = {0,0,0,0,0,0,  6,0,2,0,24,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,6,30,6,12,0,  18,24,0,6,18,0};
	
	prepareTest(places);
	
	size_t place = 24;
	Direction_read(outgoing, place);

	size_t result = Direction_getNext(outgoing);
	
	assert(result == 30 && result == places[26] && "A direction supplies the place of the next direction in the chain.");
	
	demolishTest();
}

void it_gets_deleted_with_reconnection()
{
    // 6 -> 12
    // 6 -> 18 gets deleted
	//                 0             6              12              18               24               30
	size_t places[] = {0,0,0,0,0,0,  6,0,2,0,24,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,30,0,6,12,0,  18,6,24,6,18,0};
	//                                                                                                ^ outgoing
	
	prepareTest(places);
	
	Direction_setPool(outgoing, nextOutgoing);
	
	size_t place = 30;
	Direction_read(outgoing, place);
	
	Direction_delete(outgoing);
	
	assert((*outgoing->node) == 0 && places[30] == 0 && "All fields of a deleted direction are set to zero.");
	assert((*outgoing->previous) == 0 && places[31] == 0 && "All fields of a deleted direction are set to zero.");
	assert((*outgoing->next) == 0 && places[32] == 0 && "All fields of a deleted direction are set to zero.");
	assert((*nextOutgoing->previous) == 6 && places[25] == 6 && "The previous direction gets reconnected.");
	
	demolishTest();
}

void it_gets_deleted_without_reconnection()
{
    // 6 -> 12
	//                 0             6              12              18
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	//                                                               ^ outgoing
	
	prepareTest(places);
	
	Direction_setPool(outgoing, nextOutgoing);
	
	size_t place = 18;
	Direction_read(outgoing, place);
	
	Direction_delete(outgoing);
	
	assert((*outgoing->node) == 0 && places[18] == 0 && "All fields of a deleted direction are set to zero.");
	assert((*outgoing->previous) == 0 && places[19] == 0 && "All fields of a deleted direction are set to zero.");
	assert((*outgoing->next) == 0 && places[20] == 0 && "All fields of a deleted direction are set to zero.");
	
	demolishTest();
}

void it_forbids_zero_when_getting_appended()
{
    // 6 -> 12
	//                 0             6              12              18
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	//                                                               ^ outgoing
	prepareTest(places);
	
	size_t place = 18;
	Direction_read(outgoing, place);
	
	size_t previous = 0;
	Direction_append(outgoing, previous);
	
	assert(0 == strcmp(error->method, "DirectionError_forbidZeroPlaceForPrevious"));
	assert(previous == error->previous && "DirectionError_forbidZeroPlaceForPrevious previous");
	
	demolishTest();
}

void it_forbids_zero_when_getting_deleted()
{
    // 6 -> 12
	//                 0             6              12              18 +
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,0,0,6,12,0};
	//                                                               ^ outgoing
	prepareTest(places);
	
	size_t place = 18;
	Direction_read(outgoing, place);
	
	size_t previous = 0;
	Direction_delete(outgoing);
	
	assert(0 == strcmp(error->method, "DirectionError_forbidZeroPlaceForPrevious"));
	assert(previous == error->previous && "DirectionError_forbidZeroPlaceForPrevious previous");
	
	demolishTest();
}

void it_validates_before_joining_chain()
{
    // 6 -> 12
	//                 0             6              12              18 
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,0,0,6,12,0};
	//                                                               ^ outgoing
	prepareTest(places);
	
	size_t place = 18;
	Direction_read(outgoing, place);
	
	size_t previous = 0;
	size_t next = 0;
	Direction_joinChain(outgoing, previous, next);
	
	assert(0 == strcmp(error->method, "DirectionError_forbidZeroAndEqualtyForPreviousAndNext"));
	assert(previous == error->previous && "DirectionError_forbidZeroAndEqualtyForPreviousAndNext previous");
	assert(next == error->next && "DirectionError_forbidZeroAndEqualtyForPreviousAndNext next");
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_contructs_an_outgoing_direction();
	it_contructs_an_incoming_direction();
	it_accepts_help_structures_to_avoid_eternal_cycle_when_constructing();
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
	it_forbids_zero_when_getting_appended();
	it_forbids_zero_when_getting_deleted();
	it_validates_before_joining_chain();

	return (EXIT_SUCCESS);
}


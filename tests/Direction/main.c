#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Direction.c"

void test_it_contructs_an_outgoing_direction()
{
	size_t places[6] = {1, 2, 3, 4, 5, 6};
	struct Direction * direction = Direction_constructOutgoing(places);
	
	assert(direction->places == places && "A direction can access data in this store.");
	assert(direction->offset == 0 && "An outgoing direction starts at the beginning of an entry.");
	assert(direction->nextDirection == NULL && "A new direction is not connected to any other direction.");
}

void test_it_contructs_an_imcoming_direction()
{
	size_t places[6] = {1, 2, 3, 4, 5, 6};
	struct Direction * direction = Direction_constructIncoming(places);
	
	assert(direction->places == places && "A direction can access data in this store.");
	assert(direction->offset == 3 && "An incoming direction starts right after the outgoing direction.");
	assert(direction->nextDirection == NULL && "A new direction is not connected to any other direction.");
}

void test_it_accepts_help_structures_to_avoid_eternal_cycle_when_constructing()
{
	size_t places[6] = {1, 2, 3, 4, 5, 6};
	struct Direction * direction = Direction_constructIncoming(places);
	
	struct Direction * nextDirection = Direction_constructIncoming(places);
	Direction_setPool(direction, nextDirection);
	
	assert(direction->nextDirection == nextDirection && "A direction requires a helping set of pointers to operate on the next direction.");
}

void test_it_supplies_its_place_inside_the_storage_array()
{
	size_t places[6] = {1, 2, 3, 4, 5, 6};
	struct Direction * direction = Direction_constructIncoming(places);
	
	size_t place = 0;
	Direction_bind(direction, place);
	
	size_t result = Direction_getPlace(direction);
	
	assert(result == place && "A direction keeps the place it is bound to inside the storage array.");
}

void test_it_writes_values_of_a_fresh_direction_to_the_store()
{
	size_t places[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	struct Direction * direction = Direction_constructIncoming(places);
	
	size_t place = 0;
	size_t destination = 6;
	Direction_create(direction, place, destination);
	
	assert((*direction->node) == destination && places[3] == destination && "A direction keeps the node it points to.");
	assert((*direction->previous) == 0 && places[4] == 0 && "A new direction is not connected to any previous direction.");
	assert((*direction->next) == 0 && places[5] == 0 && "A new direction is not connected to any following direction.");
}

void test_it_reads_values_of_an_existing_direction_from_the_store()
{
	size_t places[12] = {1, 2, 3, 4, 5, 6};
	struct Direction * direction = Direction_constructIncoming(places);
	
	size_t place = 0;
	Direction_read(direction, place);
	
	assert(direction->place == place && "A direction keeps the place it is bound to inside the storage array.");
	assert((*direction->node) == 4 && "A direction keeps the node it points to.");
	assert((*direction->previous) == 5 && "A direction can be connected to a previous direction.");
	assert((*direction->next) == 6 && "A new direction can be connected to a following direction.");
}

void test_it_joins_chain_of_directions()
{
	size_t places[18] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
	
	struct Direction * previousDirection = Direction_constructIncoming(places);
	size_t previousPlace = 0;
	Direction_read(previousDirection, previousPlace);
	
	struct Direction * direction = Direction_constructIncoming(places);
	size_t place = 6;
	Direction_read(direction, place);
	
	struct Direction * nextDirection = Direction_constructIncoming(places);
	size_t nextPlace = 12;
	Direction_read(nextDirection, nextPlace);
	
	Direction_joinChain(direction, previousPlace, nextPlace);

	assert((*direction->previous) == previousPlace && places[10] == previousPlace && "A direction gets connected to a previous direction.");
	assert((*direction->next) == nextPlace && places[11] == nextPlace && "A new direction gets connected to a following direction.");
}

void test_it_gets_appended_to_a_previous_direction()
{
	size_t places[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	
	struct Direction * direction = Direction_constructIncoming(places);
	size_t place = 6;
	Direction_read(direction, place);
	
	size_t previousPlace = 0;
	Direction_append(direction, previousPlace);
	
	assert((*direction->previous) == previousPlace && places[10] == previousPlace && "A direction gets connected to a previous direction.");
}

void test_it_confirms_directing_to_a_particular_node()
{
	size_t places[12] = {1, 2, 3, 4, 5, 6};
	struct Direction * direction = Direction_constructIncoming(places);
	
	size_t place = 0;
	Direction_read(direction, place);
	
	size_t nodePlace = 4;
	size_t result = Direction_hasNode(direction, nodePlace);
	
	assert(result == 1 && "A direction confirms it points to a particular node.");
}

void test_it_denies_directing_to_a_particular_node()
{
	size_t places[12] = {1, 2, 3, 4, 5, 6};
	struct Direction * direction = Direction_constructIncoming(places);
	
	size_t place = 0;
	Direction_read(direction, place);
	
	size_t nodePlace = 90;
	size_t result = Direction_hasNode(direction, nodePlace);
	
	assert(result == 0 && "A direction denies it points to a particular node.");
}

void test_it_supplies_the_node_it_directs_to()
{
    // 6 -> 12
	size_t places[24] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	struct Direction * direction = Direction_constructOutgoing(places);
	
	size_t place = 18;
	Direction_read(direction, place);

	size_t result = Direction_getNode(direction);
	
	assert(result == 12 && result == places[18] && "A direction supplies the place a node occupies that it points to.");
}

void test_it_supplies_the_place_of_the_next_direction()
{
    // 6 -> 12
    // 6 -> 18
	size_t places[36] = {0,0,0,0,0,0,  6,0,2,0,24,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,6,30,6,12,0,  18,24,0,6,18,0};
	struct Direction * direction = Direction_constructOutgoing(places);
	
	size_t place = 24;
	Direction_read(direction, place);

	size_t result = Direction_getNext(direction);
	
	assert(result == 30 && result == places[26] && "A direction supplies the place of the next direction in the chain.");
}

void test_it_gets_deleted_with_reconnection()
{
    // 6 -> 12
    // 6 -> 18
	size_t places[36] = {0,0,0,0,0,0,  6,0,2,0,24,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,6,30,6,12,0,  18,24,0,6,18,0};
	
	struct Direction * direction = Direction_constructOutgoing(places);
	
	struct Direction * nextDirection = Direction_constructOutgoing(places);
	Direction_setPool(direction, nextDirection);
	
	size_t place = 24;
	Direction_read(direction, place);
	
	Direction_delete(direction);
	
	assert((*direction->node) == 0 && places[24] == 0 && "All fields of a deleted direction are set to zero.");
	assert((*direction->previous) == 0 && places[25] == 0 && "All fields of a deleted direction are set to zero.");
	assert((*direction->next) == 0 && places[26] == 0 && "All fields of a deleted direction are set to zero.");
	assert((*nextDirection->previous) == 6 && places[31] == 6 && "The previous direction gets reconnected.");
}

void test_it_gets_deleted_without_reconnection()
{
    // 6 -> 12
	size_t places[24] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	
	struct Direction * direction = Direction_constructOutgoing(places);
	
	struct Direction * nextDirection = Direction_constructOutgoing(places);
	Direction_setPool(direction, nextDirection);
	
	size_t place = 18;
	Direction_read(direction, place);
	
	Direction_delete(direction);
	
	assert((*direction->node) == 0 && places[18] == 0 && "All fields of a deleted direction are set to zero.");
	assert((*direction->previous) == 0 && places[19] == 0 && "All fields of a deleted direction are set to zero.");
	assert((*direction->next) == 0 && places[20] == 0 && "All fields of a deleted direction are set to zero.");
}

int main(int argc, char** argv)
{
	test_it_contructs_an_outgoing_direction();
	test_it_contructs_an_imcoming_direction();
	test_it_accepts_help_structures_to_avoid_eternal_cycle_when_constructing();
	test_it_supplies_its_place_inside_the_storage_array();
	test_it_writes_values_of_a_fresh_direction_to_the_store();
	test_it_reads_values_of_an_existing_direction_from_the_store();
	test_it_joins_chain_of_directions();
	test_it_gets_appended_to_a_previous_direction();
	test_it_confirms_directing_to_a_particular_node();
	test_it_denies_directing_to_a_particular_node();
	test_it_supplies_the_node_it_directs_to();
	test_it_supplies_the_place_of_the_next_direction();
	test_it_gets_deleted_with_reconnection();
	test_it_gets_deleted_without_reconnection();

	return (EXIT_SUCCESS);
}


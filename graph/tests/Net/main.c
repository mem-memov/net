#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Net.c"
#include "../NetError.c"
#include "../Mesh.c"
#include "../Place.c"
#include "../Space.c"
#include "../Stream.c"

struct Net * net;

size_t entrySize;
struct Place * placeSize;
struct Place * nextPlace;
struct Place * gapPlace;
struct Mesh * mesh;
struct Space * space;
struct NetError * error;

void prepareTest()
{
	entrySize = 6;
	placeSize = Place_mock();
	nextPlace = Place_mock();
	gapPlace = Place_mock();
	mesh = Mesh_mock();
	space = Space_mock();
	error = NetError_mock();
	
	net = Net_construct(entrySize, placeSize, nextPlace, gapPlace, mesh, space, error);
}

void demolishTest()
{
	Net_destruct(net);
	NetError_destruct(error);
}

void it_writes_new_net_to_store()
{
	prepareTest();
	
	size_t placeSizeInBytes = 4;
	
	Net_create(net, placeSizeInBytes);
	
	// bind
	assert(
		0 == strcmp(placeSize->method[0], "Place_bind") 
		&& placeSize->position[0] == 1
	);
	assert(
		0 == strcmp(nextPlace->method[0], "Place_bind") 
		&& nextPlace->position[0] == 2
	);
	assert(
		0 == strcmp(gapPlace->method[0], "Place_bind") 
		&& gapPlace->position[0] == 3
	);
	
	// set
	assert(
		0 == strcmp(placeSize->method[1], "Place_set") 
		&& placeSize->value[1] == placeSizeInBytes
	);
	assert(
		0 == strcmp(nextPlace->method[1], "Place_set") 
		&& nextPlace->value[1] == entrySize
	);
	assert(
		0 == strcmp(gapPlace->method[1], "Place_set") 
		&& gapPlace->value[1] == 0
	);
	
	demolishTest();
}

void it_reads_values_of_an_existing_net_from_the_store()
{
	prepareTest();
	
	Net_read(net);
	
	// bind
	assert(
		0 == strcmp(placeSize->method[0], "Place_bind") 
		&& placeSize->position[0] == 1
	);
	assert(
		0 == strcmp(nextPlace->method[0], "Place_bind") 
		&& nextPlace->position[0] == 2
	);
	assert(
		0 == strcmp(gapPlace->method[0], "Place_bind") 
		&& gapPlace->position[0] == 3
	);
	
	demolishTest();
}

void it_denies_having_entry_below()
{
	prepareTest();
	
	size_t place = 2;
	
	char result = Net_hasEntry(net, place);
	
	assert(result == 0);
	
	demolishTest();
}

void it_denies_having_entry_above()
{
	prepareTest();
	
	size_t place = 2000;
	
	nextPlace->value[0] = 60;
	
	char result = Net_hasEntry(net, place);
	
	assert(0 == strcmp(nextPlace->method[0], "Place_get"));
	
	assert(result == 0);
	
	demolishTest();
}

void it_confirms_having_entry_inside()
{
	prepareTest();
	
	size_t place = 30;
	
	nextPlace->value[0] = 60;
	
	char result = Net_hasEntry(net, place);
	
	assert(0 == strcmp(nextPlace->method[0], "Place_get"));
	
	assert(result == 1);
	
	demolishTest();
}

void it_checks_if_another_entry_possible()
{
	prepareTest();
	
	nextPlace->value[0] = 300;
	gapPlace->value[0] = 120;
	
	char result = Net_canCreateEntry(net);
	
	assert(0 == strcmp(nextPlace->method[0], "Place_get"));
	
	assert(0 == strcmp(gapPlace->method[0], "Place_get"));
	
	assert(
		0 == strcmp(space->method[0], "Space_canTakeAnotherEntry") 
		&& space->nextPlace[0] == 300
		&& space->gapPlace[0] == 120
	);
	
	demolishTest();
}

void it_creates_entry_when_no_gaps()
{
	prepareTest();
	
	gapPlace->value[0] = 0;
	nextPlace->value[0] = 300;
	
	size_t result = Net_createEntry(net);
	
	assert(0 == strcmp(gapPlace->method[0], "Place_get"));
	
	assert(0 == strcmp(nextPlace->method[0], "Place_get"));
	
	assert(
		0 == strcmp(nextPlace->method[0], "Place_set") 
		&& nextPlace->value[0] == 306
	);
	
	assert(result = 300);
	
	demolishTest();
}

void it_creates_entry_using_gaps()
{
	prepareTest();
	
	gapPlace->value[0] = 120;
	mesh->nextGapPlace[0] = 72;
	
	size_t result = Net_createEntry(net);
	
	assert(0 == strcmp(gapPlace->method[0], "Place_get"));
	
	assert(
		0 == strcmp(mesh->method[0], "Mesh_removeGap") 
		&& mesh->place[0] == 120
	);
	
	assert(
		0 == strcmp(gapPlace->method[0], "Place_set") 
		&& gapPlace->value[0] == 72
	);
	
	assert(result = 120);
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_writes_new_net_to_store();
	it_reads_values_of_an_existing_net_from_the_store();
	it_denies_having_entry_below();
	it_denies_having_entry_above();
	it_confirms_having_entry_inside();
	it_checks_if_another_entry_possible();
	it_creates_entry_when_no_gaps();
	it_creates_entry_using_gaps();

	return (EXIT_SUCCESS);
}
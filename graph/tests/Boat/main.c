#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Boat.c"
#include "../Count.c"
#include "../Export.c"
#include "../Exports.c"
#include "../Knitter.c"
#include "../BoatError.c"
#include "../Place.c"
#include "../Stream.c"

struct Boat * boat;
size_t graphSize;
size_t entrySize; 
struct Exports * exports;
struct Place * one;
struct Count * nodeCount;
struct Count * linkCount;
struct Knitter * knitter;
struct BoatError * error;

void prepareTest()
{
	graphSize = 100;
	entrySize = 6;
	exports = Exports_mock();
	one = Place_mock();
	nodeCount = Count_mock();
	linkCount = Count_mock();
	knitter = Knitter_mock();
	error = BoatError_mock();
	
	boat = Boat_construct(graphSize, entrySize, exports, one, nodeCount, linkCount, knitter, error);
}

void demolishTest()
{
	Boat_destruct(boat);
	BoatError_destruct(error);
	Exports_destruct(exports);
}

void it_writes_new_boat_to_store()
{
	prepareTest();
	
	size_t placeSizeByteLength = 4;
	
	Boat_create(boat, placeSizeByteLength);
	
	assert(
		0 == strcmp(one->method[0], "Place_bind") 
		&& one->position[0] == 0
	);
	assert(0 == strcmp(knitter->method[0], "Knitter_read"));
	assert(
		0 == strcmp(nodeCount->method[0], "Count_bind") 
		&& nodeCount->position[0] == 4
	);
	assert(
		0 == strcmp(linkCount->method[0], "Count_bind") 
		&& linkCount->position[0] == 5
	);
	
	assert(
		0 == strcmp(one->method[1], "Place_set") 
		&& one->value[1] == 1
	);
	assert(
		0 == strcmp(knitter->method[1], "Knitter_create") 
		&& knitter->placeSize[1] == placeSizeByteLength
	);
	assert(0 == strcmp(nodeCount->method[1], "Count_create"));
	assert(0 == strcmp(linkCount->method[1], "Count_create"));
	
	demolishTest();
}

void it_reads_boat_fields_from_store()
{
	prepareTest();
	
	Boat_read(boat);
	
	assert(
		0 == strcmp(one->method[0], "Place_bind") 
		&& one->position[0] == 0
	);
	assert(0 == strcmp(knitter->method[0], "Knitter_read"));
	assert(
		0 == strcmp(nodeCount->method[0], "Count_bind") 
		&& nodeCount->position[0] == 4
	);
	assert(
		0 == strcmp(linkCount->method[0], "Count_bind") 
		&& linkCount->position[0] == 5
	);
		
	demolishTest();
}

void it_checks_if_place_covered_by_boat()
{
	prepareTest();
	
	size_t place = 18;
	
	knitter->hasCreatedEntry[0] = 1;
	
	char result = Boat_isCovering(boat, place);
	
	assert(0 == strcmp(knitter->method[0], "Knitter_hasCreatedEntry"));
	
	assert(result == 1);
	
	demolishTest();
}

void it_checks_free_space()
{
	prepareTest();
	
	knitter->canCreateEntry[0] = 0;
	
	char result = Boat_hasSpaceForEntry(boat);
	
	assert(0 == strcmp(knitter->method[0], "Knitter_canCreateEntry"));
	
	assert(result == 0);
	
	demolishTest();
}

void it_creates_link_entry()
{
	prepareTest();
	
	size_t place = 72;
	char hasFreeSpace = 1;
	
	knitter->canCreateEntry[0] = hasFreeSpace;
	knitter->place[1] = place;
	
	size_t result = Boat_createLinkEntry(boat);
	
	assert(0 == strcmp(knitter->method[0], "Knitter_canCreateEntry"));
	
	assert(
		0 == strcmp(error->method[0], "BoatError_requireFreeSpaceAvailable") 
		&& error->isAvailable[0] == hasFreeSpace
	);
	
	assert(0 == strcmp(knitter->method[1], "Knitter_createEntry"));
	
	assert(0 == strcmp(linkCount->method[0], "Count_increment"));
	
	assert(result == place);
	
	demolishTest();
}

void it_creates_node_entry()
{
	prepareTest();
	
	size_t place = 72;
	char hasFreeSpace = 1;
	
	knitter->canCreateEntry[0] = hasFreeSpace;
	knitter->place[1] = place;
	
	size_t result = Boat_createNodeEntry(boat);
	
	assert(0 == strcmp(knitter->method[0], "Knitter_canCreateEntry"));
	
	assert(
		0 == strcmp(error->method[0], "BoatError_requireFreeSpaceAvailable") 
		&& error->isAvailable[0] == hasFreeSpace
	);
	
	assert(0 == strcmp(knitter->method[1], "Knitter_createEntry"));
	
	assert(0 == strcmp(nodeCount->method[0], "Count_increment"));
	
	assert(result == place);
	
	demolishTest();
}

void it_deletes_link_entry()
{
	prepareTest();
	
	size_t place = 72;
	
	Boat_deleteLinkEntry(boat, place);
	
	assert(
		0 == strcmp(knitter->method[0], "Knitter_deleteEntry") 
		&& knitter->place[0] == place
	);
	
	assert(0 == strcmp(linkCount->method[0], "Count_decrement"));
	
	demolishTest();
}

void it_deletes_node_entry()
{
	prepareTest();
	
	size_t place = 72;
	
	Boat_deleteNodeEntry(boat, place);
	
	assert(
		0 == strcmp(knitter->method[0], "Knitter_deleteEntry") 
		&& knitter->place[0] == place
	);
	
	assert(0 == strcmp(nodeCount->method[0], "Count_decrement"));
	
	demolishTest();
}

void it_creates_export()
{
	prepareTest();
	
	size_t size = 200;
	
	knitter->size[0] = size;
	
	struct Export * export = Export_mock();
	exports->export[0] = export;
	
	struct Export * result = Boat_createExport(boat);
	
	assert(0 == strcmp(knitter->method[0], "Knitter_calculateSize"));

	assert(
		0 == strcmp(exports->method[0], "Exports_make") 
		&& exports->size[0] == size
	);
	
	assert(result == export);
	
	demolishTest();
}

void it_imports_stream()
{
	prepareTest();
	
	one->value[0] = 1;
	
	struct Stream * stream = Stream_mock();
	
	Boat_import(boat, stream);
	
	assert(0 == strcmp(one->method[0], "Place_get"));
	
	assert(
		0 == strcmp(error->method[0], "BoatError_requireOboatoVerifyCorrectPlaceSize") 
		&& error->one[0] == 1
	);
	
	assert(
		0 == strcmp(knitter->method[0], "Knitter_import") 
		&& knitter->stream[0] == stream
		&& knitter->graphSize[0] == boat->graphSize
	);
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_writes_new_boat_to_store();
	it_reads_boat_fields_from_store();
	it_checks_if_place_covered_by_boat();
	it_checks_free_space();
	it_creates_link_entry();
	it_creates_node_entry();
	it_deletes_link_entry();
	it_deletes_node_entry();
	it_creates_export();
	it_imports_stream();

	return (EXIT_SUCCESS);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Net.c"
#include "../Count.c"
#include "../Export.c"
#include "../Exports.c"
#include "../Knitter.c"
#include "../NetError.c"
#include "../Place.c"
#include "../Stream.c"

struct Net * net;
size_t graphSize;
size_t entrySize; 
struct Exports * exports;
struct Place * one;
struct Count * nodeCount;
struct Count * linkCount;
struct Knitter * knitter;
struct NetError * error;

void prepareTest()
{
	graphSize = 100;
	entrySize = 6;
	exports = Exports_mock();
	one = Place_mock();
	nodeCount = Count_mock();
	linkCount = Count_mock();
	knitter = Knitter_mock();
	error = NetError_mock();
	
	net = Net_construct(graphSize, entrySize, exports, one, nodeCount, linkCount, knitter, error);
}

void demolishTest()
{
	Net_destruct(net);
	NetError_destruct(error);
	Exports_destruct(exports);
}

void it_writes_new_net_to_store()
{
	prepareTest();
	
	size_t placeSizeByteLength = 4;
	
	Net_create(net, placeSizeByteLength);
	
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

void it_reads_net_fields_from_store()
{
	prepareTest();
	
	Net_read(net);
	
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

void it_checks_if_place_covered_by_net()
{
	prepareTest();
	
	size_t place = 18;
	
	knitter->hasCreatedEntry[0] = 1;
	
	char result = Net_isCovering(net, place);
	
	assert(0 == strcmp(knitter->method[0], "Knitter_hasCreatedEntry"));
	
	assert(result == 1);
	
	demolishTest();
}

void it_checks_free_space()
{
	prepareTest();
	
	knitter->canCreateEntry[0] = 0;
	
	char result = Net_hasSpaceForEntry(net);
	
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
	
	size_t result = Net_createLinkEntry(net);
	
	assert(0 == strcmp(knitter->method[0], "Knitter_canCreateEntry"));
	
	assert(
		0 == strcmp(error->method[0], "NetError_requireFreeSpaceAvailable") 
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
	
	size_t result = Net_createNodeEntry(net);
	
	assert(0 == strcmp(knitter->method[0], "Knitter_canCreateEntry"));
	
	assert(
		0 == strcmp(error->method[0], "NetError_requireFreeSpaceAvailable") 
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
	
	Net_deleteLinkEntry(net, place);
	
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
	
	Net_deleteNodeEntry(net, place);
	
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
	
	struct Export * result = Net_createExport(net);
	
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
	
	Net_import(net, stream);
	
	assert(0 == strcmp(one->method[0], "Place_get"));
	
	assert(
		0 == strcmp(error->method[0], "NetError_requireOneToVerifyCorrectPlaceSize") 
		&& error->one[0] == 1
	);
	
	assert(
		0 == strcmp(knitter->method[0], "Knitter_import") 
		&& knitter->stream[0] == stream
		&& knitter->graphSize[0] == net->graphSize
	);
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_writes_new_net_to_store();
	it_reads_net_fields_from_store();
	it_checks_if_place_covered_by_net();
	it_checks_free_space();
	it_creates_link_entry();
	it_creates_node_entry();
	it_deletes_link_entry();
	it_deletes_node_entry();
	it_creates_export();
	it_imports_stream();

	return (EXIT_SUCCESS);
}
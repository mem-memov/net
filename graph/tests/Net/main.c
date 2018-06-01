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

int main(int argc, char** argv)
{
	it_writes_new_net_to_store();
	it_reads_net_fields_from_store();
	it_checks_if_place_covered_by_net();
	it_checks_free_space();

	return (EXIT_SUCCESS);
}
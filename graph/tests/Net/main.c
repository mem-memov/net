#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Net.c"
#include "../Count.c"
#include "../Export.c"
#include "../Exports.c"
#include "../Mesh.c"
#include "../NetError.c"
#include "../Place.c"
#include "../Stream.c"

struct Net * net;
size_t graphSize;
size_t entrySize; 
struct Mesh * mesh;
struct Exports * exports;
struct Place * one;
struct Place * placeSize;
struct Place * nextPlace;
struct Place * gapPlace;
struct Count * nodeCount;
struct Count * linkCount;
struct NetError * error;

void prepareTest()
{
	graphSize = 100;
	entrySize = 6;
	mesh = Mesh_mock();
	exports = Exports_mock();
	one = Place_mock();
	placeSize = Place_mock();
	nextPlace = Place_mock();
	gapPlace = Place_mock();
	nodeCount = Count_mock();
	linkCount = Count_mock();
	error = NetError_mock();
	
	net = Net_construct(graphSize, entrySize, mesh, exports, one, placeSize, nextPlace, gapPlace, nodeCount, linkCount, error);
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
		0 == strcmp(placeSize->method[1], "Place_set") 
		&& placeSize->value[1] == placeSizeByteLength
	);
	assert(
		0 == strcmp(nextPlace->method[1], "Place_set") 
		&& nextPlace->value[1] == entrySize
	);
	assert(
		0 == strcmp(gapPlace->method[1], "Place_set") 
		&& gapPlace->value[1] == 0
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

void it_confirms_place_covered_by_net()
{
	prepareTest();
	
	size_t place = 18;
	
	nextPlace->value[0] = 36;
	
	char result = Net_isCovering(net, place);
	
	assert(0 == strcmp(nextPlace->method[0], "Place_get"));
	
	assert(result == 1);
	
	demolishTest();
}

void it_denies_place_covered_by_net_when_place_in_head()
{
	prepareTest();
	
	size_t place = 2;

	char result = Net_isCovering(net, place);

	assert(result == 0);
	
	demolishTest();
}

void it_denies_place_covered_by_net_when_behind_naxt_place()
{
	prepareTest();
	
	size_t place = 60;
	
	nextPlace->value[0] = 36;
	
	char result = Net_isCovering(net, place);
	
	assert(0 == strcmp(nextPlace->method[0], "Place_get"));
	
	assert(result == 0);
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_writes_new_net_to_store();
	it_reads_net_fields_from_store();
	it_confirms_place_covered_by_net();
	it_denies_place_covered_by_net_when_place_in_head();
	it_denies_place_covered_by_net_when_behind_naxt_place();

	return (EXIT_SUCCESS);
}
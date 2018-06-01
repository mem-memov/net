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
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_writes_new_net_to_store();

	return (EXIT_SUCCESS);
}
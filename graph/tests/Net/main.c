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
	nodeCount = Place_mock();
	linkCount = Place_mock();
	error = NetError_mock();
	
	net = Net_construct(graphSize, entrySize, mesh, exports, one, placeSize, nextPlace, gapPlace, nodeCount, linkCount, error);
}

void demolishTest()
{
	Net_destruct(net);
	Error_destruct(error);
	Exports_destruct(exports);
}

int main(int argc, char** argv)
{
	

	return (EXIT_SUCCESS);
}
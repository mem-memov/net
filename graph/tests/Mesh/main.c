#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Mesh.c"
#include "../Gap.c"

struct Mesh * mesh;
struct Gap * gap;
struct Gap * nextGap;

void prepareTest()
{
	gap = Gap_mock();
	nextGap = Gap_mock();
	
	mesh = Mesh_construct(gap, nextGap);
}

void demolishTest()
{
	Mesh_destruct(mesh);
}

void it_adds_first_gap()
{
	prepareTest();

	Mesh_addGap(mesh, 36, 0);

	assert(
		0 == strcmp(gap->method[0], "Gap_create") 
		&& gap->place[0] == 36
		&& gap->nextGapPlace[0] == 0
		&& gap->count[0] == 1
	);	
	
	demolishTest();
}

void it_adds_subsequent_gap()
{
	prepareTest();
	
	size_t place = 36;
	size_t nextGapPlace = 72;
	size_t incrementedCount = 1001;
	
	nextGap->incrementedCount[1] = incrementedCount;
	
	Mesh_addGap(mesh, place, nextGapPlace);
	
	assert(
		0 == strcmp(nextGap->method[0], "Gap_read") 
		&& nextGap->place[0] == nextGapPlace
	);	
	
	assert(0 == strcmp(nextGap->method[1], "Gap_increment"));	
	
	assert(
		0 == strcmp(gap->method[0], "Gap_create") 
		&& gap->place[0] == place
		&& gap->nextGapPlace[0] == nextGapPlace
		&& gap->count[0] == incrementedCount
	);	
	
	demolishTest();
}

void it_removes_gap()
{
	prepareTest();
	
	size_t place = 36;
	size_t nextGapPlace = 72;
	
	gap->nextGapPlace[1] = nextGapPlace;
	
	size_t result = Mesh_removeGap(mesh, place);
	
	assert(
		0 == strcmp(gap->method[0], "Gap_read") 
		&& gap->place[0] == place
	);	
	
	assert(0 == strcmp(gap->method[1], "Gap_getNext"));
	
	assert(0 == strcmp(gap->method[2], "Gap_delete"));
	
	assert(result == nextGapPlace);
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_adds_first_gap();
	it_adds_subsequent_gap();
	it_removes_gap();

	return (EXIT_SUCCESS);
}
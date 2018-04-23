#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Node.c"
#include "Link.c"

struct Node * node;
struct Link * link;

void prepareTest(size_t * places)
{
	link = Link_mock();
	node = Node_construct(places, link);
}

void demolishTest()
{
	Node_destruct(node);
}

void it_writes_new_node_to_store()
{
    // 6 -> 12
	//                 0             6
	size_t places[] = {0,0,0,0,0,0,  9,9,9,9,9,9};
	//                               ^ node
	prepareTest(places);
	
	size_t place = 6;
	Node_create(node, place);
	
	assert((*node->place) == place && places[6] == place  && "A node is identified by its place.");
	assert((*node->data) == 0 && places[7] == 0  && "A new node has no data.");
	assert((*node->outgoingLinkCount) == 0 && places[8] == 0  && "A new node has an empty counter of outgoing connections.");
	assert((*node->incomingLinkCount) == 0 && places[9] == 0  && "A new node has an empty counter of incoming connections.");
	assert((*node->outgoingLink) == 0 && places[10] == 0  && "A new node has no outgoing connections.");
	assert((*node->incomingLink) == 0 && places[11] == 0  && "A new node has no incoming connections.");
	
	demolishTest();
}

void it_reads_values_of_an_existing_node_from_the_store()
{
	//                 0             6                 12              18               24              30
	size_t places[] = {0,0,0,0,0,0,  6,555,1,1,24,30,  12,0,0,1,0,24,  18,0,1,0,0,30,   12,6,0,6,12,0,  6,18,0,18,6,0};
	//                               ^ node            ^ node           ^ node          ^ 6 -> 12       ^ 18 -> 6
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	assert((*node->place) == 6  && "A node is identified by its place.");
	assert((*node->data) == 555  && "A node may have some data.");
	assert((*node->outgoingLinkCount) == 1  && "A node keeps count of outgoing connections.");
	assert((*node->incomingLinkCount) == 1  && "A node keeps count of incoming connections.");
	assert((*node->outgoingLink) == 24  && "A node can have the last outgoing connection.");
	assert((*node->incomingLink) == 30  && "A node can have the last incoming connections.");
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_writes_new_node_to_store();
	it_reads_values_of_an_existing_node_from_the_store();

	return (EXIT_SUCCESS);
}


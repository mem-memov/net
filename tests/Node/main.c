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

void it_supplies_its_place()
{
	//                 0             6
	size_t places[] = {0,0,0,0,0,0,  6,0,0,0,0,0};
	//                               ^ node
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	size_t result = Node_getPlace(node);
	
	assert(result == place  && "A node supplies its place.");
	
	demolishTest();
}

void it_denies_to_be_a_node_if_place_not_equal_value()
{
	//                 0             6
	size_t places[] = {0,0,0,0,0,0,  555,0,0,0,0,0};
	//                               ^ node
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	char result = Node_isNode(node);
	
	assert(result == 0  && "A node is identified by its place.");
	
	demolishTest();
}

void it_denies_to_be_a_node_if_zero()
{
	//                 0
	size_t places[] = {0,0,0,0,0,0};
	//                 ^ node
	prepareTest(places);
	
	size_t place = 0;
	Node_read(node, place);
	
	char result = Node_isNode(node);
	
	assert(result == 0  && "Zero has special meaning. A node can't be at place zero.");
	
	demolishTest();
}

void it_confirms_to_be_an_entry_of_type_node()
{
	//                 0             6
	size_t places[] = {0,0,0,0,0,0,  6,0,0,0,0,0};
	//                               ^ node
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	char result = Node_isNode(node);
	
	assert(result == 1  && "A node is an entry with place written to that place.");
	
	demolishTest();
}

void it_denies_having_incoming_links()
{
	//                 0             6     +   +
	size_t places[] = {0,0,0,0,0,0,  6,0,0,0,0,0};
	//                               ^ node
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	char result = Node_hasIncomingLink(node);
	
	assert(result == 0  && "A node may have no incoming connections.");
	
	demolishTest();
}

void it_confirms_having_incoming_links()
{
	//                 0             6              12     +   +    18               24              30
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,24,0,  12,0,0,2,0,30,  18,0,0,1,0,30,   12,6,0,6,30,0,  12,18,0,18,12,24};
	//                               ^ node         ^ node           ^ node          ^ 6 -> 12       ^ 18 -> 12
	prepareTest(places);
	
	size_t place = 12;
	Node_read(node, place);
	
	char result = Node_hasIncomingLink(node);
	
	assert(result == 1  && "A node can have one incoming link, the most fresh in the chain of incoming connections.");
	
	demolishTest();
}


void it_denies_having_outgoing_links()
{
	//                 0             6     +   +
	size_t places[] = {0,0,0,0,0,0,  6,0,0,0,0,0};
	//                               ^ node
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	char result = Node_hasOutgoingLink(node);
	
	assert(result == 0  && "A node may have no outgoing connections.");
	
	demolishTest();
}

void it_confirms_having_outgoing_links()
{
	//                 0             6              12              18               24 +             30
	size_t places[] = {0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,30,0,6,12,0,  18,6,24,6,18,0};
	//                               ^ node         ^ node           ^ node          ^ 6 -> 12        ^ 6 -> 18
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	char result = Node_hasOutgoingLink(node);
	
	assert(result == 1  && "A node can have one outgoing link, the most fresh in the chain of outgoing connections.");
	
	demolishTest();
}

void it_keeps_the_first_incoming_connection()
{
	//                 0             6              12     +   +   18
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,0,0,0,  12,6,0,6,12,0};
	//                               ^ node         ^ node          ^ 6 -> 12
	prepareTest(places);
	
	size_t place = 12;
	Node_read(node, place);
	
	struct Link * incomingLink = Link_mock();
	incomingLink->result[1] = 18;
	Node_addIncomingLink(node, incomingLink);

	assert(0 == strcmp(incomingLink->method[0], "Link_shiftIncoming"));
	assert(place == incomingLink->previous[0] && "Link_shiftIncoming previous");
	
	assert(0 == strcmp(incomingLink->method[1], "Link_getPlace"));
	assert(1 == places[15] && "Incoming link count gets incremented.");
	assert(18 == places[17] && "A node keeps its first incoming link.");
	
	demolishTest();
}

void it_keeps_the_latest_incoming_connection()
{
	//                 0             6              12     +   +    18               24              30
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,24,0,  12,0,0,1,0,24,  18,0,0,1,0,30,   12,6,0,6,30,0,  12,18,0,18,12,24};
	//                               ^ node         ^ node           ^ node          ^ 6 -> 12       ^ 18 -> 12
	prepareTest(places);
	
	size_t place = 12;
	Node_read(node, place);
	
	struct Link * incomingLink = Link_mock();
	incomingLink->result[1] = 30;
	Node_addIncomingLink(node, incomingLink);
	
	assert(0 == strcmp(incomingLink->method[0], "Link_joinIncoming"));
	assert(12 == incomingLink->previous[0] && "Link_joinIncoming previous");
	assert(24 == incomingLink->next[0] && "Link_joinIncoming next");
	
	assert(0 == strcmp(link->method[0], "Link_read"));
	
	assert(0 == strcmp(link->method[1], "Link_shiftIncoming"));
	assert(30 == link->previous[1] && "Link_shiftIncoming previous");
	
	//assert(30 == strcmp(incomingLink->method[1], "Link_getPlace"));
	//assert(2 == places[15] && "Incoming link count gets incremented.");
	//assert(30 == places[17] && "A node keeps its latest incoming link.");
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_writes_new_node_to_store();
	it_reads_values_of_an_existing_node_from_the_store();
	it_supplies_its_place();
	it_denies_to_be_a_node_if_place_not_equal_value();
	it_denies_to_be_a_node_if_zero();
	it_confirms_to_be_an_entry_of_type_node();
	it_denies_having_incoming_links();
	it_confirms_having_incoming_links();
	it_denies_having_outgoing_links();
	it_confirms_having_outgoing_links();
	it_keeps_the_first_incoming_connection();
	it_keeps_the_latest_incoming_connection();

	return (EXIT_SUCCESS);
}


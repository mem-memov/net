#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Node.c"
#include "../Count.c"
#include "../Link.c"
#include "../NodeError.c"
#include "../Place.c"
#include "../Star.c"

struct Node * node;
struct Place * place;
struct Place * data;
struct Count * outgoingLinkCount;
struct Count * incomingLinkCount;
struct Place * outgoingLink;
struct Place * incomingLink;
struct NodeError * error;
struct Star * star;

void prepareTest()
{
	place = Place_mock();
	data = Place_mock();
	outgoingLinkCount = Count_mock();
	incomingLinkCount = Count_mock();
	outgoingLink = Place_mock();
	incomingLink = Place_mock();
	star = Star_mock();
	error = NodeError_mock();
	node = Node_construct(place, data, outgoingLinkCount, incomingLinkCount, outgoingLink, incomingLink, star, error);
}

void demolishTest()
{
	Node_destruct(node);
	NodeError_destruct(error);
}

void it_writes_new_node_to_store()
{
	prepareTest();
	
	size_t placeInStore = 6;
	Node_create(node, placeInStore);
	
	// bind
	assert(
		0 == strcmp(place->method[0], "Place_bind") 
		&& place->position[0] == 6
	);
	assert(
		0 == strcmp(data->method[0], "Place_bind") 
		&& data->position[0] == 7
	);
	assert(
		0 == strcmp(outgoingLinkCount->method[0], "Count_bind") 
		&& outgoingLinkCount->position[0] == 8
	);
	assert(
		0 == strcmp(incomingLinkCount->method[0], "Count_bind") 
		&& incomingLinkCount->position[0] == 9
	);
	assert(
		0 == strcmp(outgoingLink->method[0], "Place_bind") 
		&& outgoingLink->position[0] == 10
	);
	assert(
		0 == strcmp(incomingLink->method[0], "Place_bind") 
		&& incomingLink->position[0] == 11
	);
	
	// set
	assert(
		0 == strcmp(place->method[1], "Place_set") 
		&& place->value[1] == placeInStore
	);
	assert(
		0 == strcmp(data->method[1], "Place_set") 
		&& data->value[1] == 0
	);
	assert(0 == strcmp(outgoingLinkCount->method[1], "Count_create"));
	assert(0 == strcmp(incomingLinkCount->method[1], "Count_create"));
	assert(
		0 == strcmp(outgoingLink->method[1], "Place_set") 
		&& outgoingLink->value[1] == 0
	);
	assert(
		0 == strcmp(incomingLink->method[1], "Place_set") 
		&& incomingLink->value[1] == 0
	);

	demolishTest();
}

void it_reads_values_of_an_existing_node_from_the_store()
{
	prepareTest();
	
	size_t placeInStore = 6;
	Node_read(node, placeInStore);
	
	// bind
	assert(
		0 == strcmp(place->method[0], "Place_bind") 
		&& place->position[0] == 6
	);
	assert(
		0 == strcmp(data->method[0], "Place_bind") 
		&& data->position[0] == 7
	);
	assert(
		0 == strcmp(outgoingLinkCount->method[0], "Count_bind") 
		&& outgoingLinkCount->position[0] == 8
	);
	assert(
		0 == strcmp(incomingLinkCount->method[0], "Count_bind") 
		&& incomingLinkCount->position[0] == 9
	);
	assert(
		0 == strcmp(outgoingLink->method[0], "Place_bind") 
		&& outgoingLink->position[0] == 10
	);
	assert(
		0 == strcmp(incomingLink->method[0], "Place_bind") 
		&& incomingLink->position[0] == 11
	);
	
	demolishTest();
}

void it_deletes_node()
{
	prepareTest();

	size_t outgoingLinkPlace = 0;
	size_t incomingLinkPlace = 0;
	outgoingLink->value[0] = outgoingLinkPlace;
	incomingLink->value[0] = incomingLinkPlace;
	Node_delete(node);

	assert(0 == strcmp(outgoingLink->method[0], "Place_get"));
	assert(0 == strcmp(incomingLink->method[0], "Place_get"));

	assert(
		0 == strcmp(error->method[0], "NodeError_forbidDeletingNodeWithConnections") 
		&& error->outgoingLink[0] == outgoingLinkPlace
		&& error->incomingLink[0] == incomingLinkPlace
	);
	
	assert(
		0 == strcmp(place->method[0], "Place_set") 
		&& place->value[0] == 0
	);
	assert(
		0 == strcmp(data->method[0], "Place_set") 
		&& data->value[0] == 0
	);
	assert(0 == strcmp(outgoingLinkCount->method[0], "Count_delete"));
	assert(0 == strcmp(incomingLinkCount->method[0], "Count_delete"));
	
	demolishTest();
}

void it_supplies_its_place()
{
	prepareTest();
	
	size_t placeInStore = 6;
	place->value[0] = placeInStore ;
	
	size_t result = Node_getPlace(node);
	
	assert(0 == strcmp(place->method[0], "Place_get"));
	assert(result == placeInStore  && "A node supplies its place.");
	
	demolishTest();
}

void it_denies_to_be_a_node_if_place_not_equal_value()
{
	prepareTest();

	place->keepsPosition[0] = 0;
	char result = Node_isNode(node);
	
	assert(0 == strcmp(place->method[0], "Place_keepsPosition"));
	
	assert(result == 0  && "A node is identified by its place.");
	
	demolishTest();
}

void it_denies_to_be_a_node_if_zero()
{
	prepareTest();
	
	place->keepsPosition[0] = 1;
	place->value[1] = 0;
	char result = Node_isNode(node);
	
	assert(0 == strcmp(place->method[0], "Place_keepsPosition"));
	assert(0 == strcmp(place->method[1], "Place_get"));
	assert(result == 0  && "Zero has special meaning. A node can't be at place zero.");
	
	demolishTest();
}

void it_confirms_to_be_an_entry_of_type_node()
{
	prepareTest();
	
	place->keepsPosition[0] = 1;
	place->value[1] = 6;
	char result = Node_isNode(node);
	
	assert(0 == strcmp(place->method[0], "Place_keepsPosition"));
	assert(0 == strcmp(place->method[1], "Place_get"));
	assert(result == 1  && "A node is an entry with place written to that place.");
	
	demolishTest();
}

void it_keeps_the_first_incoming_connection()
{
	// 0             6 node         12 node        18 12->6
	// 0,0,0,0,0,0,  6,0,0,0,0,0,   12,0,0,0,0,0,  6,0,0,12,0,0
	// 0,0,0,0,0,0,  6,0,0,0,0,0,   12,0,0,0,0,0,  6,0,0,12,6,0 1) The first link (18) in the incoming chain gets destination node (6) 
	//                                                      ^   as a predecessor in the incoming chain.
	// 0,0,0,0,0,0,  6,0,0,0,0,18,  12,0,0,0,0,0,  6,0,0,12,6,0 2) The destination node (6) keeps the link (18) as the beginning of the chain 
	//                         ^                                of incoming connections from other nodes.
	// 0,0,0,0,0,0,  6,0,0,1,0,18,  12,0,0,0,0,0,  6,0,0,12,6,0 3) The destination node (6) increments the length of the chain of connections 
	//                     ^                                    coming from other nodes.
	prepareTest();
	
	size_t nodePlace = 6;
	size_t incomingLinkPlace = 18;

	struct Link * addedIncomingLink = Link_mock();
	addedIncomingLink->place[0] = incomingLinkPlace;

	place->value[0] = nodePlace;
	incomingLinkCount->isZero[0] = 1;
	
	Node_addIncomingLink(node, addedIncomingLink);
	
	assert(0 == strcmp(place->method[0], "Place_get"));
	
	assert(0 == strcmp(addedIncomingLink->method[0], "Link_getPlace"));

	assert(0 == strcmp(incomingLinkCount->method[0], "Count_isZero"));

	assert(
		0 == strcmp(addedIncomingLink->method[1], "Link_shiftIncoming")
		&& addedIncomingLink->previousIncomingLink[1] == nodePlace
	);

	assert(
		0 == strcmp(incomingLink->method[0], "Place_set")
		&& incomingLink->value[0] == incomingLinkPlace
	);
	
	assert(0 == strcmp(incomingLinkCount->method[1], "Count_increment"));
	
	demolishTest();
}

void it_keeps_the_latest_incoming_connection()
{
	//                 0             6 node         12 node         18 node          24 12->6        30 18->6
	size_t places[] = {0,0,0,0,0,0,  6,0,0,1,0,24,  12,0,1,0,24,0,  18,0,0,0,0,0,    6,12,0,12,6,0,  18,0,0,6,0,0};
	//                 0,0,0,0,0,0,  6,0,0,1,0,24,  12,0,1,0,24,0,  18,0,0,0,0,0,    6,12,0,12,6,0,  18,0,0,6,6,24 1) The new link (30) comes after the destination node (6)
	//                                                                                                        ^ ^  and before the old link (24).
	//                 0,0,0,0,0,0,  6,0,0,1,0,24,  12,0,1,0,24,0,  18,0,0,0,0,0,    6,12,0,12,30,0, 18,0,0,6,6,24 2) The old link (24) gets shifted after the new
	//                                                                                         ^                   link (30).
	//                 0,0,0,0,0,0,  6,0,0,1,0,30,  12,0,1,0,24,0,  18,0,0,0,0,0,    6,12,0,12,30,0, 18,0,0,6,6,24 3) The destination node (6) throws old link (24) away
	//                                         ^                                                                   and keeps new link (30) instead.
	//                 0,0,0,0,0,0,  6,0,0,2,0,30,  12,0,1,0,24,0,  18,0,0,0,0,0,    6,12,0,12,30,0, 18,0,0,6,6,24 4) The destination node (6) increments the length of the 
	//                                     ^                                                                       chain of connections going out to other nodes.

	prepareTest();

	size_t nodePlace = 6;
	size_t oldIncomingLinkPlace = 24;
	size_t newIncomingLinkPlace = 30;

	struct Link * addedIncomingLink = Link_mock();
	addedIncomingLink->place[0] = newIncomingLinkPlace;
	
	place->value[0] = nodePlace;
	incomingLinkCount->isZero[0] = 0;
	incomingLink->value[0] = oldIncomingLinkPlace;
	
	Node_addIncomingLink(node, addedIncomingLink);
	
	assert(0 == strcmp(place->method[0], "Place_get"));
	
	assert(0 == strcmp(addedIncomingLink->method[0], "Link_getPlace"));
	
	assert(0 == strcmp(incomingLinkCount->method[0], "Count_isZero"));
	
	assert(0 == strcmp(incomingLink->method[0], "Place_get"));
	
	assert(
		0 == strcmp(addedIncomingLink->method[1], "Link_joinIncoming")
		&& addedIncomingLink->previousIncomingLink[1] == nodePlace
		&& addedIncomingLink->nextIncomingLink[1] == oldIncomingLinkPlace
	);
	
	assert(
		0 == strcmp(star->method[0], "Star_addIncomingLink")
		&& star->oldIncomingLink[0] == oldIncomingLinkPlace
		&& star->newIncomingLink[0] == newIncomingLinkPlace
	);
	
	assert(
		0 == strcmp(incomingLink->method[1], "Place_set")
		&& incomingLink->value[1] == newIncomingLinkPlace
	);
	
	assert(0 == strcmp(incomingLinkCount->method[1], "Count_increment"));

	demolishTest();
}

void it_keeps_the_first_outgoing_connection()
{
	//                 0             6 node         12 node        18 6->12
	size_t places[] = {0,0,0,0,0,0,  6,0,0,0,0,0,   12,0,0,0,0,0,  12,0,0,6,0,0};
	//                 0,0,0,0,0,0,  6,0,0,0,0,0,   12,0,0,0,0,0,  12,6,0,0,0,0 1) The first link (18) in the outgoing chain gets origin node (6)  
	//                                                                ^         as a predecessor in the outgoing chain.
	//                 0,0,0,0,0,0,  6,0,0,0,18,0,  12,0,0,0,0,0,  12,6,0,0,0,0 2) The origin node (6) keeps the link (18) as the beginning of the chain 
	//                                       ^                                  of outgoing connections to other nodes.
	//                 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,0,0,0,  12,6,0,0,0,0 3) The origin node (6) increments the length of the chain of connections 
	//                                   ^                                      going out to other nodes.
	
	prepareTest();
	
	size_t nodePlace = 6;
	size_t outgoingLinkPlace = 18;
	
	struct Link * addedOutgoingLink = Link_mock();
	addedOutgoingLink->place[0] = outgoingLinkPlace;
	
	place->value[0] = nodePlace;
	outgoingLinkCount->isZero[0] = 1;
	
	Node_addOutgoingLink(node, addedOutgoingLink);
	
	assert(0 == strcmp(place->method[0], "Place_get"));
	
	assert(0 == strcmp(addedOutgoingLink->method[0], "Link_getPlace"));
	
	assert(0 == strcmp(outgoingLinkCount->method[0], "Count_isZero"));
	
	assert(
		0 == strcmp(addedOutgoingLink->method[1], "Link_shiftOutgoing")
		&& addedOutgoingLink->previousOutgoingLink[1] == nodePlace
	);

	assert(
		0 == strcmp(outgoingLink->method[0], "Place_set")
		&& outgoingLink->value[0] == outgoingLinkPlace
	);
	
	assert(0 == strcmp(outgoingLinkCount->method[1], "Count_increment"));

	demolishTest();
}

void it_keeps_the_latest_outgoing_connection()
{
	//                 0             6 node         12 node         18 node          24 6->12         30 6->18
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,24,0,  12,0,0,1,0,24,  18,0,0,0,0,0,    12,6,0,6,12,0,   18,0,0,6,0,0};
	//                 0,0,0,0,0,0,  6,0,1,0,24,0,  12,0,0,1,0,24,  18,0,0,0,0,0,    12,6,0,6,12,0,   18,6,24,6,0,0 1) The new link (30) comes after the origin node (6)
	//                                                                                                   ^ ^        and before the old link (24).
	//                 0,0,0,0,0,0,  6,0,1,0,24,0,  12,0,0,1,0,24,  18,0,0,0,0,0,    12,30,0,6,12,0,  18,6,24,6,0,0 2) The old link (24) gets shifted after the new
	//                                                                                  ^                           link (30).
	//                 0,0,0,0,0,0,  6,0,1,0,30,0,  12,0,0,1,0,24,  18,0,0,0,0,0,    12,30,0,6,12,0,  18,6,24,6,0,0 3) The origin node (6) throws old link (24) away
	//                                       ^                                                                      and keeps new link (30) instead.
	//                 0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,0,0,0,    12,30,0,6,12,0,  18,6,24,6,0,0 4) The origin node (6) increments the length of the 
	//                                   ^                                                                          chain of connections going out to other nodes.

	prepareTest();
	
	size_t nodePlace = 6;
	size_t oldOutgoingLinkPlace = 24;
	size_t newOutgoingLinkPlace = 30;
	
	struct Link * addedOutgoingLink = Link_mock();
	addedOutgoingLink->place[0] = newOutgoingLinkPlace;
	
	place->value[0] = nodePlace;
	outgoingLinkCount->isZero[0] = 0;
	outgoingLink->value[0] = oldOutgoingLinkPlace;
	
	Node_addOutgoingLink(node, addedOutgoingLink);
	
	assert(0 == strcmp(place->method[0], "Place_get"));
	
	assert(0 == strcmp(addedOutgoingLink->method[0], "Link_getPlace"));
	
	assert(0 == strcmp(outgoingLinkCount->method[0], "Count_isZero"));
	
	assert(0 == strcmp(outgoingLink->method[0], "Place_get"));

	assert(
		0 == strcmp(addedOutgoingLink->method[1], "Link_joinOutgoing")
		&& addedOutgoingLink->previousOutgoingLink[1] == nodePlace
		&& addedOutgoingLink->nextOutgoingLink[1] == oldOutgoingLinkPlace
	);
	
	assert(
		0 == strcmp(star->method[0], "Star_addOutgoingLink")
		&& star->oldOutgoingLink[0] == oldOutgoingLinkPlace
		&& star->newOutgoingLink[0] == newOutgoingLinkPlace
	);
	
	assert(
		0 == strcmp(outgoingLink->method[1], "Place_set")
		&& outgoingLink->value[1] == newOutgoingLinkPlace
	);
	
	assert(0 == strcmp(outgoingLinkCount->method[1], "Count_increment"));

	demolishTest();
}

void it_provides_its_outgoing_link()
{
	// 0             6 node         12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	//                       ^
	prepareTest();

	struct Link * readOutgoingLink = Link_mock();
	
	size_t outgoingLinkPlace = 18;
	outgoingLink->value[0] = outgoingLinkPlace;
	
	Node_readOutgoingLink(node, readOutgoingLink);
	
	assert(0 == strcmp(outgoingLink->method[0], "Place_get"));
	
	assert(
		0 == strcmp(error->method[0], "NodeError_forbidReadingOutgoingLinkWhenNonePresent")
		&& error->outgoingLink[0] == outgoingLinkPlace
	);
	
	assert(
		0 == strcmp(readOutgoingLink->method[0], "Link_read")
		&& readOutgoingLink->place[0] == outgoingLinkPlace
	);

	demolishTest();
}

void it_provides_its_incoming_link()
{
	// 0             6 node         12 node         18 12->6
	// 0,0,0,0,0,0,  6,0,0,1,0,18,  12,0,1,0,18,0,  6,12,0,12,6,0
	//                         ^
	prepareTest();

	struct Link * readIncomingLink = Link_mock();
	
	size_t incomingLinkPlace = 18;
	incomingLink->value[0] = incomingLinkPlace;
	
	Node_readIncomingLink(node, readIncomingLink);
	
	assert(0 == strcmp(incomingLink->method[0], "Place_get"));
	
	assert(
		0 == strcmp(error->method[0], "NodeError_forbidReadingIncomingLinkWhenNonePresent")
		&& error->incomingLink[0] == incomingLinkPlace
	);
	
	assert(
		0 == strcmp(readIncomingLink->method[0], "Link_read")
		&& readIncomingLink->place[0] == incomingLinkPlace
	);

	demolishTest();
}

void it_deletes_outgoing_link()
{
	// 0             6 node         12 node         18 node           24 6->12         30 6->18
	// 0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,1,0,30,    12,30,0,6,12,0,  18,6,24,6,18,0
	//                   ^   ^
	
	prepareTest();

	outgoingLinkCount->value[0] = 2;
	outgoingLinkCount->isZero[2] = 0;
	
	Node_deleteOutgoingLink(node);
	
	assert(0 == strcmp(outgoingLinkCount->method[0], "Count_get"));
	
	assert(
		0 == strcmp(error->method[0], "NodeError_forbidDeletingOutgoingLinkWhenNonePresent")
		&&  error->outgoingLinkCount[0] == 2
	);
	
	assert(0 == strcmp(outgoingLinkCount->method[1], "Count_decrement"));
	
	assert(0 == strcmp(outgoingLinkCount->method[2], "Count_isZero"));

	demolishTest();
}

void it_deletes_last_outgoing_link()
{
	// 0             6 node         12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	//                   ^   ^
	
	prepareTest();
	
	outgoingLinkCount->value[0] = 1;
	outgoingLinkCount->isZero[2] = 1;

	Node_deleteOutgoingLink(node);
	
	assert(0 == strcmp(outgoingLinkCount->method[0], "Count_get"));
	
	assert(
		0 == strcmp(error->method[0], "NodeError_forbidDeletingOutgoingLinkWhenNonePresent")
		&&  error->outgoingLinkCount[0] == 1
	);
	
	assert(0 == strcmp(outgoingLinkCount->method[1], "Count_decrement"));
	
	assert(0 == strcmp(outgoingLinkCount->method[2], "Count_isZero"));
	
	assert(
		0 == strcmp(outgoingLink->method[0], "Place_set")
		&& outgoingLink->value[0] == 0
	);

	demolishTest();
}

void it_deletes_incoming_link()
{
	// 0             6 node         12 node         18 node           24 12->6        30 18->6
	// 0,0,0,0,0,0,  6,0,0,2,0,30,  12,0,1,0,24,0,  18,0,1,0,30,0,    6,12,0,12,30,0, 18,18,0,6,6,24
	//                     ^   ^
	
	prepareTest();

	incomingLinkCount->value[0] = 2;
	incomingLinkCount->isZero[2] = 0;
	
	Node_deleteIncomingLink(node);
	
	assert(0 == strcmp(incomingLinkCount->method[0], "Count_get"));
	
	assert(
		0 == strcmp(error->method[0], "NodeError_forbidDeletingIncomingLinkWhenNonePresent")
		&&  error->incomingLinkCount[0] == 2
	);

	assert(0 == strcmp(incomingLinkCount->method[1], "Count_decrement"));
	
	assert(0 == strcmp(incomingLinkCount->method[2], "Count_isZero"));
	
	demolishTest();
}

void it_deletes_last_incoming_link()
{
	// 0             6 node         12 node         18 12->6
	// 0,0,0,0,0,0,  6,0,0,1,0,18,  12,0,1,0,0,18,  6,12,0,12,6,0
	//                     ^   ^
	
	prepareTest();
	
	incomingLinkCount->value[0] = 1;
	incomingLinkCount->isZero[2] = 1;
	
	Node_deleteIncomingLink(node);
	
	assert(0 == strcmp(incomingLinkCount->method[0], "Count_get"));
	
	assert(
		0 == strcmp(error->method[0], "NodeError_forbidDeletingIncomingLinkWhenNonePresent")
		&&  error->incomingLinkCount[0] == 1
	);

	assert(0 == strcmp(incomingLinkCount->method[1], "Count_decrement"));
	
	assert(0 == strcmp(incomingLinkCount->method[2], "Count_isZero"));
	
	assert(
		0 == strcmp(incomingLink->method[0], "Place_set")
		&& incomingLink->value[0] == 0
	);
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_writes_new_node_to_store();
	it_reads_values_of_an_existing_node_from_the_store();
	it_deletes_node();
	it_supplies_its_place();
	it_denies_to_be_a_node_if_place_not_equal_value();
	it_denies_to_be_a_node_if_zero();
	it_confirms_to_be_an_entry_of_type_node();
	it_keeps_the_first_incoming_connection();
	it_keeps_the_latest_incoming_connection();
	it_keeps_the_first_outgoing_connection();
	it_keeps_the_latest_outgoing_connection();
	it_provides_its_outgoing_link();
	it_provides_its_incoming_link();
	it_deletes_outgoing_link();
	it_deletes_last_outgoing_link();
	it_deletes_incoming_link();
	it_deletes_last_incoming_link();

	return (EXIT_SUCCESS);
}


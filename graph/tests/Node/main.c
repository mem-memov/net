#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Node.c"
#include "Count.c"
#include "Link.c"
#include "NodeError.c"
#include "Place.c"
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
	// 0             6 node
	// 0,0,0,0,0,0,  9,9,9,9,9,9
	// 0,0,0,0,0,0,  6,0,0,0,0,0

	prepareTest();
	
	size_t place = 6;
	Node_create(node, place);
	
	// bind
	assert(
		0 == strcmp(node->place->method[0], "Place_bind") 
		&& node->place->position[0] == 6
		&& "A node is identified by its place."
	);
	assert(
		0 == strcmp(node->data->method[0], "Place_bind") 
		&& node->data->position[0] == 7
		&& "A node may have some data."
	);
	assert(
		0 == strcmp(node->outgoingLinkCount->method[0], "Count_bind") 
		&& node->outgoingLinkCount->position[0] == 8
		&& "A node keeps count of outgoing connections."
	);
	assert(
		0 == strcmp(node->incomingLinkCount->method[0], "Count_bind") 
		&& node->incomingLinkCount->position[0] == 9
		&& "A node keeps count of incoming connections."
	);
	assert(
		0 == strcmp(node->outgoingLink->method[0], "Place_bind") 
		&& node->outgoingLink->position[0] == 10
		&& "A node can have the last outgoing connection."
	);
	assert(
		0 == strcmp(node->incomingLink->method[0], "Place_bind") 
		&& node->incomingLink->position[0] == 11
		&& "A node can have the last incoming connections."
	);
	
	// set
	assert(
		0 == strcmp(node->place->method[1], "Place_set") 
		&& node->place->value[1] == place
		&& "A node is identified by its place."
	);
	assert(
		0 == strcmp(node->data->method[1], "Place_set") 
		&& node->data->value[1] == 0
		&& "A new node has no data."
	);
	assert(
		0 == strcmp(node->outgoingLinkCount->method[1], "Count_create") 
		&& "A new node has an empty counter of outgoing connections."
	);
	assert(
		0 == strcmp(node->incomingLinkCount->method[1], "Count_create") 
		&& "A new node has an empty counter of incoming connections."
	);
	assert(
		0 == strcmp(node->outgoingLink->method[1], "Place_set") 
		&& node->outgoingLink->value[1] == 0
		&& "A new node has no outgoing connections."
	);
	assert(
		0 == strcmp(node->incomingLink->method[1], "Place_set") 
		&& node->incomingLink->value[1] == 0
		&& "A new node has no incoming connections."
	);

	demolishTest();
}

void it_reads_values_of_an_existing_node_from_the_store()
{
	// 0             6 node            12 node         18 node          24 6->12        30 18->6
	// 0,0,0,0,0,0,  6,555,1,1,24,30,  12,0,0,1,0,24,  18,0,1,0,0,30,   12,6,0,6,12,0,  6,18,0,18,6,0
	//               
	prepareTest();
	
	size_t place = 6;
	Node_read(node, place);
	
	// bind
	assert(
		0 == strcmp(node->place->method[0], "Place_bind") 
		&& node->place->position[0] == 6
		&& "A node is identified by its place."
	);
	assert(
		0 == strcmp(node->data->method[0], "Place_bind") 
		&& node->data->position[0] == 7
		&& "A node may have some data."
	);
	assert(
		0 == strcmp(node->outgoingLinkCount->method[0], "Count_bind") 
		&& node->outgoingLinkCount->position[0] == 8
		&& "A node keeps count of outgoing connections."
	);
	assert(
		0 == strcmp(node->incomingLinkCount->method[0], "Count_bind") 
		&& node->incomingLinkCount->position[0] == 9
		&& "A node keeps count of incoming connections."
	);
	assert(
		0 == strcmp(node->outgoingLink->method[0], "Place_bind") 
		&& node->outgoingLink->position[0] == 10
		&& "A node can have the last outgoing connection."
	);
	assert(
		0 == strcmp(node->incomingLink->method[0], "Place_bind") 
		&& node->incomingLink->position[0] == 11
		&& "A node can have the last incoming connections."
	);
	
	demolishTest();
}

void it_deletes_node()
{
	// 0             6 node
	// 0,0,0,0,0,0,  6,0,0,0,0,0

	prepareTest();
	
	size_t place = 6;
	size_t outgoingLink = 0;
	size_t incomingLink = 0;
	node->outgoingLink->value[0] = outgoingLink;
	node->incomingLink->value[0] = incomingLink;
	Node_delete(node);

	assert(0 == strcmp(node->outgoingLink->method[0], "Place_get"));
	assert(0 == strcmp(node->incomingLink->method[0], "Place_get"));

	assert(
		0 == strcmp(error->method, "NodeError_forbidDeletingNodeWithConnections") 
		&& outgoingLink == error->outgoingLink 
		&& incomingLink == error->incomingLink
	);
	
	assert(
		0 == strcmp(node->place->method[0], "Place_set") 
		&& node->place->value[0] == 0
		&& "All fields of a deleted node are set to zero."
	);
	assert(
		0 == strcmp(node->data->method[0], "Place_set") 
		&& node->data->value[0] == 0
		&& "All fields of a deleted node are set to zero."
	);
	assert(
		0 == strcmp(node->outgoingLinkCount->method[0], "Count_delete") 
		&& "All fields of a deleted node are set to zero."
	);
	assert(
		0 == strcmp(node->incomingLinkCount->method[0], "Count_delete") 
		&& "All fields of a deleted node are set to zero."
	);
	
	demolishTest();
}

void it_supplies_its_place()
{
	// 0             6 node
	// 0,0,0,0,0,0,  6,0,0,0,0,0
	
	prepareTest();
	
	size_t place = 6;
	node->place->value[0] = place;
	
	size_t result = Node_getPlace(node);
	
	assert(0 == strcmp(node->place->method[0], "Place_get"));
	assert(result == place  && "A node supplies its place.");
	
	demolishTest();
}

void it_denies_to_be_a_node_if_place_not_equal_value()
{
	// 0             6 node
	// 0,0,0,0,0,0,  555,0,0,0,0,0
	
	prepareTest();

	node->place->keepsPosition[0] = 0;
	char result = Node_isNode(node);
	
	assert(0 == strcmp(node->place->method[0], "Place_keepsPosition"));
	
	assert(result == 0  && "A node is identified by its place.");
	
	demolishTest();
}

void it_denies_to_be_a_node_if_zero()
{
	// 0
	// 0,0,0,0,0,0
	
	prepareTest();
	
	node->place->keepsPosition[0] = 1;
	node->place->value[1] = 0;
	char result = Node_isNode(node);
	
	assert(0 == strcmp(node->place->method[0], "Place_keepsPosition"));
	assert(0 == strcmp(node->place->method[1], "Place_get"));
	assert(result == 0  && "Zero has special meaning. A node can't be at place zero.");
	
	demolishTest();
}

void it_confirms_to_be_an_entry_of_type_node()
{
	// 0             6 node
	// 0,0,0,0,0,0,  6,0,0,0,0,0
	
	prepareTest();
	
	node->place->keepsPosition[0] = 1;
	node->place->value[1] = 6;
	char result = Node_isNode(node);
	
	assert(0 == strcmp(node->place->method[0], "Place_keepsPosition"));
	assert(0 == strcmp(node->place->method[1], "Place_get"));
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

	struct Link * incomingLink = Link_mock();
	incomingLink->place[0] = incomingLinkPlace;

	node->place->value[0] = nodePlace;
	node->incomingLinkCount->isZero[0] = 1;
	
	Node_addIncomingLink(node, incomingLink);
	
	assert(0 == strcmp(node->place->method[0], "Place_get"));
	
	assert(0 == strcmp(incomingLink->method[0], "Link_getPlace"));

	assert(0 == strcmp(node->incomingLinkCount->method[0], "Count_isZero"));

	assert(
		0 == strcmp(incomingLink->method[1], "Link_shiftIncoming")
		&& incomingLink->previousIncomingLink[1] == nodePlace
	);

	assert(
		0 == strcmp(node->incomingLink->method[0], "Place_set")
		&& node->incomingLink->value[0] == incomingLinkPlace
	);
	
	assert(0 == strcmp(node->incomingLinkCount->method[1], "Count_increment"));
	
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

	struct Link * incomingLink = Link_mock();
	incomingLink->place[0] = newIncomingLinkPlace;
	
	node->place->value[0] = nodePlace;
	node->incomingLinkCount->isZero[0] = 0;
	node->incomingLink->value[0] = oldIncomingLinkPlace;
	
	Node_addIncomingLink(node, incomingLink);
	
	assert(0 == strcmp(node->place->method[0], "Place_get"));
	
	assert(0 == strcmp(incomingLink->method[0], "Link_getPlace"));
	
	assert(0 == strcmp(node->incomingLinkCount->method[0], "Count_isZero"));
	
	assert(0 == strcmp(node->incomingLink->method[0], "Place_get"));
	
	assert(
		0 == strcmp(incomingLink->method[1], "Link_joinIncoming")
		&& incomingLink->previousIncomingLink[1] == nodePlace
		&& incomingLink->nextIncomingLink[1] == oldIncomingLinkPlace
	);
	
	assert(
		0 == strcmp(star->method[0], "Star_addIncomingLink")
		&& star->oldIncomingLink[0] == oldIncomingLinkPlace
		&& star->newIncomingLink[0] == newIncomingLinkPlace
	);
	
	assert(
		0 == strcmp(node->incomingLink->method[1], "Place_set")
		&& node->incomingLink->value[1] == newIncomingLinkPlace
	);
	
	assert(0 == strcmp(node->incomingLinkCount->method[1], "Count_increment"));

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
	
	struct Link * outgoingLink = Link_mock();
	outgoingLink->place[0] = outgoingLinkPlace;
	
	node->place->value[0] = nodePlace;
	node->outgoingLink->isZero[0] = 1;
	
	Node_addOutgoingLink(node, outgoingLink);
	
	assert(0 == strcmp(node->place->method[0], "Place_get"));
	
	assert(0 == strcmp(outgoingLink->method[0], "Link_getPlace"));
	
	assert(0 == strcmp(node->outgoingLinkCount->method[0], "Count_isZero"));
	
	assert(
		0 == strcmp(outgoingLink->method[1], "Link_shiftOutgoing")
		&& outgoingLink->previousOutgoingLink[1] == nodePlace
	);

	assert(
		0 == strcmp(node->outgoingLink->method[0], "Place_set")
		&& node->outgoingLink->value[0] == outgoingLinkPlace
	);
	
	assert(0 == strcmp(node->outgoingLinkCount->method[1], "Count_increment"));

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
	
	struct Link * outgoingLink = Link_mock();
	outgoingLink->place[0] = newOutgoingLinkPlace;
	
	node->place->value[0] = nodePlace;
	node->outgoingLinkCount->isZero[0] = 0;
	node->outgoingLink->value[0] = oldOutgoingLinkPlace;
	
	Node_addOutgoingLink(node, outgoingLink);
	
	assert(0 == strcmp(node->place->method[0], "Place_get"));
	
	assert(0 == strcmp(outgoingLink->method[0], "Link_getPlace"));
	
	assert(0 == strcmp(node->outgoingLinkCount->method[0], "Count_isZero"));
	
	assert(0 == strcmp(node->outgoingLink->method[0], "Place_get"));

	assert(
		0 == strcmp(outgoingLink->method[1], "Link_joinOutgoing")
		&& outgoingLink->previousOutgoingLink[1] == nodePlace
		&& outgoingLink->nextOutgoingLink[1] == oldOutgoingLinkPlace
	);
	
	assert(
		0 == strcmp(star->method[0], "Star_addOutgoingLink")
		&& star->oldOutgoingLink[0] == oldOutgoingLinkPlace
		&& star->newOutgoingLink[0] == newOutgoingLinkPlace
	);
	
	assert(
		0 == strcmp(node->outgoingLink->method[1], "Place_set")
		&& node->outgoingLink->value[1] == newOutgoingLinkPlace
	);
	
	assert(0 == strcmp(node->outgoingLinkCount->method[1], "Count_increment"));

	demolishTest();
}

void it_finds_incoming_link_by_origin_node()
{
	// 0             6 node         12 node         18 12->6
	// 0,0,0,0,0,0,  6,0,0,1,0,18,  12,0,1,0,18,0,  6,12,0,12,6,0
	//                                                     ^
	
	prepareTest();

	size_t originNodePlace = 12;
	size_t incomingLinkPlace = 18;
	
	star->foundIncomingLink[0] = incomingLinkPlace;	
	
	node->incomingLinkCount->isZero[0] = 0;
	node->incomingLink->value[0] = incomingLinkPlace;

	size_t result = Node_findIncomingLink(node, originNodePlace);
	
	assert(0 == strcmp(node->incomingLinkCount->method[0], "Count_isZero"));
	
	assert(0 == strcmp(node->incomingLink->method[0], "Place_get"));
	
	assert(
		0 == strcmp(star->method[0], "Star_findIncomingLink")
		&& star->incomingLink[0] == incomingLinkPlace
		&& star->originNode[0] == originNodePlace
	);
	
	assert(result == incomingLinkPlace && "A destination node returns the link that connects it to an origin node.");

	demolishTest();
}

void it_refuses_to_find_incoming_link_when_chain_empty()
{
	//                 0             6 node
	size_t places[] = {0,0,0,0,0,0,  6,0,0,0,0,0};
	
	prepareTest();
	
	size_t originNodePlace = 12;
	
	node->incomingLinkCount->isZero[0] = 1;
	
	size_t result = Node_findIncomingLink(node, originNodePlace);
	
	assert(0 == strcmp(node->incomingLinkCount->method[0], "Count_isZero"));

	assert(0 == result && "The node notifies about failure with zero value.");
	
	demolishTest();
}

void it_finds_outgoing_link_by_destination_node()
{
	//                 0             6 node         12 node         18 12->6
	size_t places[] = {0,0,0,0,0,0,  6,0,0,1,0,18,  12,0,1,0,18,0,  6,12,0,12,6,0};
	
	prepareTest();

	size_t destinationNodePlace = 6;
	size_t outgoingLinkPlace = 18;
	
	star->foundOutgoingLink[0] = outgoingLinkPlace;
	
	node->outgoingLinkCount->isZero[0] = 0;
	node->outgoingLink->value[0] = outgoingLinkPlace;
	
	size_t result = Node_findOutgoingLink(node, destinationNodePlace);
	
	assert(0 == strcmp(node->outgoingLinkCount->method[0], "Count_isZero"));
	
	assert(0 == strcmp(node->outgoingLink->method[0], "Place_get"));

	assert(
		0 == strcmp(star->method[0], "Star_findOutgoingLink")
		&& star->outgoingLink[0] == outgoingLinkPlace
		&& star->destinationNode[0] == destinationNodePlace
	);

	assert(result == outgoingLinkPlace && "An origin node returns the link that connects it to a destination node.");
	
	demolishTest();
}

void it_refuses_to_find_outgoing_link_when_chain_empty()
{
	//                 0             6 node
	size_t places[] = {0,0,0,0,0,0,  6,0,0,0,0,0};
	
	prepareTest();
	
	size_t destinationNodePlace = 12;
	
	node->outgoingLinkCount->isZero[0] = 1;
	
	size_t result = Node_findOutgoingLink(node, destinationNodePlace);
	
	assert(0 == strcmp(node->outgoingLinkCount->method[0], "Count_isZero"));

	assert(0 == result && "The node notifies about failure with zero value.");
	
	demolishTest();
}

void it_provides_its_outgoing_link()
{
	// 0             6 node         12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	//                       ^
	prepareTest();

	struct Link * outgoingLink = Link_mock();
	
	size_t outgoingLinkPlace = 18;
	node->outgoingLink->value[0] = outgoingLinkPlace;
	
	Node_readOutgoingLink(node, outgoingLink);
	
	assert(0 == strcmp(node->outgoingLink->method[0], "Place_get"));
	
	assert(
		0 == strcmp(error->method, "NodeError_forbidReadingOutgoingLinkWhenNonePresent")
		&& error->outgoingLink == outgoingLinkPlace
	);
	
	assert(
		0 == strcmp(outgoingLink->method[0], "Link_read")
		&& outgoingLink->place[0] == outgoingLinkPlace
	);

	demolishTest();
}

void it_provides_its_incoming_link()
{
	// 0             6 node         12 node         18 12->6
	// 0,0,0,0,0,0,  6,0,0,1,0,18,  12,0,1,0,18,0,  6,12,0,12,6,0
	//                         ^
	prepareTest();

	struct Link * incomingLink = Link_mock();
	
	size_t incomingLinkPlace = 18;
	node->incomingLink->value[0] = incomingLinkPlace;
	
	Node_readIncomingLink(node, incomingLink);
	
	assert(0 == strcmp(node->incomingLink->method[0], "Place_get"));
	
	assert(
		0 == strcmp(error->method, "NodeError_forbidReadingIncomingLinkWhenNonePresent")
		&& error->incomingLink == incomingLinkPlace
	);
	
	assert(
		0 == strcmp(incomingLink->method[0], "Link_read")
		&& incomingLink->place[0] == incomingLinkPlace
	);

	demolishTest();
}

void it_deletes_outgoing_link()
{
	// 0             6 node         12 node         18 node           24 6->12         30 6->18
	// 0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,1,0,30,    12,30,0,6,12,0,  18,6,24,6,18,0
	//                   ^   ^
	
	prepareTest();

	node->outgoingLinkCount->value[0] = 2;
	node->outgoingLinkCount->isZero[2] = 0;
	
	Node_deleteOutgoingLink(node);
	
	assert(0 == strcmp(node->outgoingLinkCount->method[0], "Count_get"));
	
	assert(
		0 == strcmp(error->method, "NodeError_forbidDeletingOutgoingLinkWhenNonePresent")
		&&  error->outgoingLinkCount == 2
	);
	
	assert(0 == strcmp(node->outgoingLinkCount->method[1], "Count_decrement"));
	
	assert(0 == strcmp(node->outgoingLinkCount->method[2], "Count_isZero"));

	demolishTest();
}

void it_deletes_last_outgoing_link()
{
	// 0             6 node         12 node         18 6->12
	// 0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0
	//                   ^   ^
	
	prepareTest();
	
	node->outgoingLinkCount->value[0] = 1;
	node->outgoingLinkCount->isZero[2] = 1;

	Node_deleteOutgoingLink(node);
	
	assert(0 == strcmp(node->outgoingLinkCount->method[0], "Count_get"));
	
	assert(
		0 == strcmp(error->method, "NodeError_forbidDeletingOutgoingLinkWhenNonePresent")
		&&  error->outgoingLinkCount == 1
	);
	
	assert(0 == strcmp(node->outgoingLinkCount->method[1], "Count_decrement"));
	
	assert(0 == strcmp(node->outgoingLinkCount->method[2], "Count_isZero"));
	
	assert(
		0 == strcmp(node->outgoingLink->method[0], "Place_set")
		&& node->outgoingLink->value[0] == 0
	);

	demolishTest();
}

void it_deletes_incoming_link()
{
	// 0             6 node         12 node         18 node           24 12->6        30 18->6
	// 0,0,0,0,0,0,  6,0,0,2,0,30,  12,0,1,0,24,0,  18,0,1,0,30,0,    6,12,0,12,30,0, 18,18,0,6,6,24
	//                     ^   ^
	
	prepareTest();

	node->incomingLinkCount->value[0] = 2;
	node->incomingLinkCount->isZero[2] = 0;
	
	Node_deleteIncomingLink(node);
	
	assert(0 == strcmp(node->incomingLinkCount->method[0], "Count_get"));
	
	assert(
		0 == strcmp(error->method, "NodeError_forbidDeletingIncomingLinkWhenNonePresent")
		&&  error->incomingLinkCount == 2
	);

	assert(0 == strcmp(node->incomingLinkCount->method[1], "Count_decrement"));
	
	assert(0 == strcmp(node->incomingLinkCount->method[2], "Count_isZero"));
	
	demolishTest();
}

void it_deletes_last_incoming_link()
{
	// 0             6 node         12 node         18 12->6
	// 0,0,0,0,0,0,  6,0,0,1,0,18,  12,0,1,0,0,18,  6,12,0,12,6,0
	//                     ^   ^
	
	prepareTest();
	
	node->incomingLinkCount->value[0] = 1;
	node->incomingLinkCount->isZero[2] = 1;
	
	Node_deleteIncomingLink(node);
	
	assert(0 == strcmp(node->incomingLinkCount->method[0], "Count_get"));
	
	assert(
		0 == strcmp(error->method, "NodeError_forbidDeletingIncomingLinkWhenNonePresent")
		&&  error->incomingLinkCount == 1
	);

	assert(0 == strcmp(node->incomingLinkCount->method[1], "Count_decrement"));
	
	assert(0 == strcmp(node->incomingLinkCount->method[2], "Count_isZero"));
	
	assert(
		0 == strcmp(node->incomingLink->method[0], "Place_set")
		&& node->incomingLink->value[0] == 0
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
	it_finds_incoming_link_by_origin_node();
	it_refuses_to_find_incoming_link_when_chain_empty();
	it_finds_outgoing_link_by_destination_node();
	it_refuses_to_find_outgoing_link_when_chain_empty();
	it_provides_its_outgoing_link();
	it_provides_its_incoming_link();
	it_deletes_outgoing_link();
	it_deletes_last_outgoing_link();
	it_deletes_incoming_link();
	it_deletes_last_incoming_link();

	return (EXIT_SUCCESS);
}


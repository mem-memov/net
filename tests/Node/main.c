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
	//                 0             6 node         12 node       18 12->6
	size_t places[] = {0,0,0,0,0,0,  6,0,0,0,0,0,   12,0,0,0,0,0,  6,0,0,12,0,0};
	//                 0,0,0,0,0,0,  6,0,0,0,0,0,   12,0,0,0,0,0,  6,0,0,12,6,0 1) The first link (18) in the incoming chain gets destination node (6) 
	//                                                                      ^   as a predecessor in the incoming chain.
	//                 0,0,0,0,0,0,  6,0,0,0,0,18,  12,0,0,0,0,0,  6,0,0,12,6,0 2) The destination node (6) keeps the link (18) as the beginning of the chain 
	//                                         ^                                of incoming connections from other nodes.
	//                 0,0,0,0,0,0,  6,0,0,1,0,18,  12,0,0,0,0,0,  6,0,0,12,6,0 3) The destination node (6) increments the length of the chain of connections 
	//                                     ^                                    coming from other nodes.
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

	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	struct Link * incomingLink = Link_mock();
	incomingLink->result[1] = 30;
	incomingLink->result[2] = 30;
	Node_addIncomingLink(node, incomingLink);
	
	assert(0 == strcmp(incomingLink->method[0], "Link_joinIncoming"));
	assert(6 == incomingLink->previous[0] && "Link_joinIncoming previous");
	assert(24 == incomingLink->next[0] && "Link_joinIncoming next");
	
	assert(0 == strcmp(link->method[0], "Link_read"));
	assert(24 == link->place[0] && "Link_read place");
	
	assert(0 == strcmp(incomingLink->method[1], "Link_getPlace"));
	
	assert(0 == strcmp(link->method[1], "Link_shiftIncoming"));
	assert(30 == link->previous[1] && "Link_shiftIncoming previous");
	
	assert(0 == strcmp(incomingLink->method[2], "Link_getPlace"));
	assert(2 == places[9] && "Incoming link count gets incremented.");
	assert(30 == places[11] && "A node keeps its latest incoming link.");
	
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
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	struct Link * outgoingLink = Link_mock();
	outgoingLink->result[1] = 18;
	Node_addOutgoingLink(node, outgoingLink);

	assert(0 == strcmp(outgoingLink->method[0], "Link_shiftOutgoing"));
	assert(place == outgoingLink->previous[0] && "Link_shiftOutgoing previous");
	
	assert(0 == strcmp(outgoingLink->method[1], "Link_getPlace"));
	assert(1 == places[8] && "Outgoing link count gets incremented.");
	assert(18 == places[10] && "A node keeps its first outgoing link.");
	
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

	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	struct Link * outgoingLink = Link_mock();
	outgoingLink->result[1] = 30;
	outgoingLink->result[2] = 30;
	Node_addOutgoingLink(node, outgoingLink);
	
	assert(0 == strcmp(outgoingLink->method[0], "Link_joinOutgoing"));
	assert(6 == outgoingLink->previous[0] && "Link_joinOutgoing previous");
	assert(24 == outgoingLink->next[0] && "Link_joinOutgoing next");
	
	assert(0 == strcmp(link->method[0], "Link_read"));
	assert(24 == link->place[0] && "Link_read place");
	
	assert(0 == strcmp(outgoingLink->method[1], "Link_getPlace"));
	
	assert(0 == strcmp(link->method[1], "Link_shiftOutgoing"));
	assert(30 == link->previous[1] && "Link_shiftOutgoing previous");
	
	assert(0 == strcmp(outgoingLink->method[2], "Link_getPlace"));
	assert(2 == places[8] && "Outgoing link count gets incremented.");
	assert(30 == places[10] && "A node keeps its latest outgoing link.");
	
	demolishTest();
}

void it_finds_incoming_link_by_origin_node_with_one_link_in_chain()
{
	//                 0             6 node         12 node         18 12->6
	size_t places[] = {0,0,0,0,0,0,  6,0,0,1,0,18,  12,0,1,0,18,0,  6,12,0,12,6,0};
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	link->result[1] = 1;
	size_t origin = 12;
	size_t result = Node_findIncomingLink(node, origin);
	
	assert(0 == strcmp(link->method[0], "Link_read"));
	assert(18 == link->place[0] && "Link_read place");
	
	assert(0 == strcmp(link->method[1], "Link_isIncomingFromNode"));
	assert(origin == link->origin[1] && "Link_isIncomingFromNode origin");
	
	assert(18 == result && "The node supplies the incoming link place.");
	
	demolishTest();
}

void it_finds_incoming_link_by_origin_node_with_many_links_in_chain()
{
	//                 0             6 node         12 node         18 node           24 12->6        30 18->6
	size_t places[] = {0,0,0,0,0,0,  6,0,0,2,0,30,  12,0,1,0,24,0,  18,0,1,0,30,0,    6,12,0,12,30,0, 18,18,0,6,6,24};
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	link->result[1] = 0;
	link->result[2] = 24;
	link->result[4] = 1;
	size_t origin = 12;
	size_t result = Node_findIncomingLink(node, origin);
	
	assert(0 == strcmp(link->method[0], "Link_read"));
	assert(30 == link->place[0] && "Link_read place");
	
	assert(0 == strcmp(link->method[1], "Link_isIncomingFromNode"));
	assert(origin == link->origin[1] && "Link_isIncomingFromNode origin");
	
	assert(0 == strcmp(link->method[2], "Link_getNextIncoming"));

	assert(0 == strcmp(link->method[3], "Link_read"));
	assert(24 == link->place[3] && "Link_read place");
	
	assert(0 == strcmp(link->method[4], "Link_isIncomingFromNode"));
	assert(origin == link->origin[4] && "Link_isIncomingFromNode origin");
	
	assert(24 == result && "The node supplies the incoming link place.");
	
	demolishTest();
}

void it_refuses_to_find_incoming_link_when_chain_empty()
{
	//                 0             6 node
	size_t places[] = {0,0,0,0,0,0,  6,0,0,0,0,0};
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	size_t origin = 12;
	size_t result = Node_findIncomingLink(node, origin);
	
	assert(0 == result && "The node notifies about failure with zero value.");
	
	demolishTest();
}

void it_refuses_to_find_incoming_link_when_node_not_in_chain()
{
	//                 0             6 node         12 node         18 node           24 12->6        30 18->6
	size_t places[] = {0,0,0,0,0,0,  6,0,0,2,0,30,  12,0,1,0,24,0,  18,0,1,0,30,0,    6,12,0,12,30,0, 18,18,0,6,6,24};
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	link->result[1] = 0;
	link->result[2] = 24;
	link->result[4] = 0;
	link->result[5] = 0;
	size_t origin = 777;
	size_t result = Node_findIncomingLink(node, origin);
	
	assert(0 == strcmp(link->method[0], "Link_read"));
	assert(30 == link->place[0] && "Link_read place");
	
	assert(0 == strcmp(link->method[1], "Link_isIncomingFromNode"));
	assert(origin == link->origin[1] && "Link_isIncomingFromNode origin");
	
	assert(0 == strcmp(link->method[2], "Link_getNextIncoming"));

	assert(0 == strcmp(link->method[3], "Link_read"));
	assert(24 == link->place[3] && "Link_read place");
	
	assert(0 == strcmp(link->method[4], "Link_isIncomingFromNode"));
	assert(origin == link->origin[4] && "Link_isIncomingFromNode origin");
	
	assert(0 == strcmp(link->method[5], "Link_getNextIncoming"));
	
	assert(0 == result && "The node notifies about failure with zero value.");
	
	demolishTest();
}

void it_finds_outgoing_link_by_destination_node_with_one_link_in_chain()
{
	//                 0             6 node         12 node         18 12->6
	size_t places[] = {0,0,0,0,0,0,  6,0,0,1,0,18,  12,0,1,0,18,0,  6,12,0,12,6,0};
	
	prepareTest(places);
	
	size_t place = 12;
	Node_read(node, place);
	
	link->result[1] = 1;
	size_t destination = 6;
	size_t result = Node_findOutgoingLink(node, destination);
	
	assert(0 == strcmp(link->method[0], "Link_read"));
	assert(18 == link->place[0] && "Link_read place");
	
	assert(0 == strcmp(link->method[1], "Link_isOutgoingToNode"));
	assert(destination == link->destination[1] && "Link_isOutgoingToNode destination");
	
	assert(18 == result && "The node supplies the outgoing link place.");
	
	demolishTest();
}

void it_finds_outgoing_link_by_destination_node_with_many_links_in_chain()
{
	//                 0             6 node         12 node         18 node           24 6->12        30 6->18
	size_t places[] = {0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,1,0,30,    12,30,0,6,12,0,  18,6,24,6,18,0};
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	link->result[1] = 0;
	link->result[2] = 24;
	link->result[4] = 1;
	size_t destination = 12;
	size_t result = Node_findOutgoingLink(node, destination);
	
	assert(0 == strcmp(link->method[0], "Link_read"));
	assert(30 == link->place[0] && "Link_read place");
	
	assert(0 == strcmp(link->method[1], "Link_isOutgoingToNode"));
	assert(destination == link->destination[1] && "Link_isOutgoingToNode destination");
	
	assert(0 == strcmp(link->method[2], "Link_getNextOutgoing"));

	assert(0 == strcmp(link->method[3], "Link_read"));
	assert(24 == link->place[3] && "Link_read place");
	
	assert(0 == strcmp(link->method[4], "Link_isOutgoingToNode"));
	assert(destination == link->destination[4] && "Link_isOutgoingToNodee destination");
	
	assert(24 == result && "The node supplies the outgoing link place.");
	
	demolishTest();
}

void it_refuses_to_find_outgoing_link_when_chain_empty()
{
	//                 0             6 node
	size_t places[] = {0,0,0,0,0,0,  6,0,0,0,0,0};
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	size_t destination = 12;
	size_t result = Node_findOutgoingLink(node, destination);
	
	assert(0 == result && "The node notifies about failure with zero value.");
	
	demolishTest();
}

void it_refuses_to_find_outgoing_link_when_node_not_in_chain()
{
	//                 0             6 node         12 node         18 node           24 6->12        30 6->18
	size_t places[] = {0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,1,0,30,    12,30,0,6,12,0,  18,6,24,6,18,0};
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	link->result[1] = 0;
	link->result[2] = 24;
	link->result[4] = 0;
	link->result[5] = 0;
	size_t destination = 777;
	size_t result = Node_findOutgoingLink(node, destination);
	
	assert(0 == strcmp(link->method[0], "Link_read"));
	assert(30 == link->place[0] && "Link_read place");
	
	assert(0 == strcmp(link->method[1], "Link_isOutgoingToNode"));
	assert(destination == link->destination[1] && "Link_isOutgoingToNode destination");
	
	assert(0 == strcmp(link->method[2], "Link_getNextOutgoing"));

	assert(0 == strcmp(link->method[3], "Link_read"));
	assert(24 == link->place[3] && "Link_read place");
	
	assert(0 == strcmp(link->method[4], "Link_isOutgoingToNode"));
	assert(destination == link->destination[4] && "Link_isOutgoingToNodee destination");
	
	assert(0 == strcmp(link->method[4], "Link_isOutgoingToNode"));
	assert(destination == link->destination[4] && "Link_isOutgoingToNode destination");
	
	assert(0 == strcmp(link->method[5], "Link_getNextOutgoing"));
	
	assert(0 == result && "The node notifies about failure with zero value.");
	
	demolishTest();
}

void it_confirms_having_more_outgoing_connections_than_incoming_ones()
{
	//                 0             6 node         12 node         18 6->12
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	char result = Node_hasMoreOutgoingLinks(node);
	
	assert(1 == result && "The node confirms having more outgoing connections than incoming.");

	demolishTest();
}

void it_denies_having_more_outgoing_connections_than_incoming_ones()
{
	//                 0             6 node         12 node         18 12->6
	size_t places[] = {0,0,0,0,0,0,  6,0,0,1,0,18,  12,0,1,0,18,0,  6,12,0,12,6,0};
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	char result = Node_hasMoreOutgoingLinks(node);
	
	assert(0 == result && "The node denies having more outgoing connections than incoming.");

	demolishTest();
}

void it_provides_its_outgoing_link()
{
	//                 0             6 node         12 node         18 6->12
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	struct Link * outgoingLink = Link_mock();
	Node_readOutgoingLink(node, outgoingLink);
	
	assert(0 == strcmp(outgoingLink->method[0], "Link_read"));
	assert(18 == outgoingLink->place[0] && "Link_read place");
	
	demolishTest();
}

void it_provides_its_incoming_link()
{
	//                 0             6 node         12 node         18 12->6
	size_t places[] = {0,0,0,0,0,0,  6,0,0,1,0,18,  12,0,1,0,18,0,  6,12,0,12,6,0};
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	struct Link * incomingLink = Link_mock();
	Node_readIncomingLink(node, incomingLink);
	
	assert(0 == strcmp(incomingLink->method[0], "Link_read"));
	assert(18 == incomingLink->place[0] && "Link_read place");
	
	demolishTest();
}

void it_deletes_outgoing_link()
{
	//                 0             6 node         12 node         18 node           24 6->12         30 6->18
	size_t places[] = {0,0,0,0,0,0,  6,0,2,0,30,0,  12,0,0,1,0,24,  18,0,0,1,0,30,    12,30,0,6,12,0,  18,6,24,6,18,0};
	//                                   ^   ^
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	Node_deleteOutgoingLink(node);
	
	assert(1 == places[8] && "The node count for outgoing connections is decremented.");
	assert(30 == places[10] && "The node keeps the outgoing link.");
	
	demolishTest();
}

void it_deletes_last_outgoing_link()
{
	//                 0             6 node         12 node         18 6->12
	size_t places[] = {0,0,0,0,0,0,  6,0,1,0,18,0,  12,0,0,1,0,18,  12,6,0,6,12,0};
	//                                   ^   ^
	
	prepareTest(places);
	
	size_t place = 6;
	Node_read(node, place);
	
	Node_deleteOutgoingLink(node);
	
	assert(0 == places[8] && "The node count for outgoing connections is set to zero.");
	assert(0 == places[10] && "The node has no outgoing link.");
	
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
	it_keeps_the_first_outgoing_connection();
	it_keeps_the_latest_outgoing_connection();
	it_finds_incoming_link_by_origin_node_with_one_link_in_chain();
	it_finds_incoming_link_by_origin_node_with_many_links_in_chain();
	it_refuses_to_find_incoming_link_when_chain_empty();
	it_refuses_to_find_incoming_link_when_node_not_in_chain();
	it_finds_outgoing_link_by_destination_node_with_one_link_in_chain();
	it_finds_outgoing_link_by_destination_node_with_many_links_in_chain();
	it_refuses_to_find_outgoing_link_when_chain_empty();
	it_refuses_to_find_outgoing_link_when_node_not_in_chain();
	it_confirms_having_more_outgoing_connections_than_incoming_ones();
	it_denies_having_more_outgoing_connections_than_incoming_ones();
	it_provides_its_outgoing_link();
	it_provides_its_incoming_link();
	it_deletes_outgoing_link();
	it_deletes_last_outgoing_link();

	return (EXIT_SUCCESS);
}


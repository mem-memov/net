#include "../../source/Link.h"
#include <stdlib.h>

struct Link {
	char call;
	size_t place[6];
	size_t previous[6];
	size_t next[6];
	size_t result[6];
	size_t origin[6];
	size_t destination[6];
	char * method[6];
};

struct Link * Link_mock()
{
	struct Link * this = malloc(sizeof(struct Link));
	
	this->call = 0;
	
	this->place[0] = 55555;
	this->previous[0] = 55555;
	this->next[0] = 55555;
	this->result[0] = 55555;
	this->origin[0] = 55555;
	this->destination[0] = 55555;
	this->method[0] = "method not specified";
	
	this->place[1] = 55555;
	this->previous[1] = 55555;
	this->next[1] = 55555;
	this->result[1] = 55555;
	this->origin[1] = 55555;
	this->destination[1] = 55555;
	this->method[1] = "method not specified";
	
	this->place[2] = 55555;
	this->previous[2] = 55555;
	this->next[2] = 55555;
	this->result[2] = 55555;
	this->origin[2] = 55555;
	this->destination[2] = 55555;
	this->method[2] = "method not specified";
	
	this->place[3] = 55555;
	this->previous[3] = 55555;
	this->next[3] = 55555;
	this->result[3] = 55555;
	this->origin[3] = 55555;
	this->destination[3] = 55555;
	this->method[3] = "method not specified";
	
	this->place[4] = 55555;
	this->previous[4] = 55555;
	this->next[4] = 55555;
	this->result[4] = 55555;
	this->origin[4] = 55555;
	this->destination[4] = 55555;
	this->method[4] = "method not specified";
	
	this->place[5] = 55555;
	this->previous[5] = 55555;
	this->next[5] = 55555;
	this->result[5] = 55555;
	this->origin[5] = 55555;
	this->destination[5] = 55555;
	this->method[5] = "method not specified";
	
	return this;
}

void Link_destruct(struct Link * this)
{
	free(this);
	this = NULL;
}

size_t Link_getPlace(struct Link * this)
{
	this->method[this->call] = "Link_getPlace";
	
	size_t place = this->result[this->call];
		
	this->call++;
	
	return place;
}

void Link_create(struct Link * this, size_t place, size_t origin, size_t destination)
{

}

void Link_read(struct Link * this, size_t place)
{
	this->place[this->call] = place;
	this->method[this->call] = "Link_read";
	this->call++;
}

void Link_joinOutgoing(struct Link * this, size_t previous, size_t next)
{
	this->previous[this->call] = previous;
	this->next[this->call] = next;
	this->method[this->call] = "Link_joinOutgoing";
	this->call++;
}

void Link_joinIncoming(struct Link * this, size_t previous, size_t next)
{
	this->previous[this->call] = previous;
	this->next[this->call] = next;
	this->method[this->call] = "Link_joinIncoming";
	this->call++;
}

void Link_shiftOutgoing(struct Link * this, size_t previous)
{
	this->previous[this->call] = previous;
	this->method[this->call] = "Link_shiftOutgoing";
	this->call++;
}

void Link_shiftIncoming(struct Link * this, size_t previous)
{
	this->previous[this->call] = previous;
	this->method[this->call] = "Link_shiftIncoming";
	this->call++;
}

char Link_isOutgoingToNode(struct Link * this, size_t destination)
{
	this->destination[this->call] = destination;
	this->method[this->call] = "Link_isOutgoingToNode";
	size_t result = this->result[this->call];
		
	this->call++;
	
	if (1 == result) {
		return 1;
	} 
	
	if (0 == result) {
		return 0;
	}
}

char Link_isIncomingFromNode(struct Link * this, size_t origin)
{
	this->origin[this->call] = origin;
	this->method[this->call] = "Link_isIncomingFromNode";
	size_t result = this->result[this->call];
		
	this->call++;
	
	if (1 == result) {
		return 1;
	} 
	
	if (0 == result) {
		return 0;
	}
}

size_t Link_getNextOutgoing(struct Link * this)
{
	this->method[this->call] = "Link_getNextOutgoing";
	size_t result = this->result[this->call];
	
	this->call++;
	
	return result;
}

size_t Link_getNextIncoming(struct Link * this)
{
	this->method[this->call] = "Link_getNextIncoming";
	size_t result = this->result[this->call];
	
	this->call++;
	
	return result;
}

void Link_delete(struct Link * this)
{

}

size_t Link_getOutgoingNode(struct Link * this)
{
	return 0;
}

size_t Link_getIncomingNode(struct Link * this)
{
	return 0;
}
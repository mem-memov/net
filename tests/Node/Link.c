#include "../../source/Link.h"
#include <stdlib.h>

struct Link {
	char call;
	size_t previous[3];
	size_t next[3];
	size_t result[3];
	char * method[3];
};

struct Link * Link_mock()
{
	struct Link * this = malloc(sizeof(struct Link));
	
	this->call = 0;
	
	this->previous[0] = 0;
	this->next[0] = 0;
	this->result[0] = 0;
	this->method[0] = "method not specified";
	
	this->previous[1] = 0;
	this->next[1] = 0;
	this->result[1] = 0;
	this->method[1] = "method not specified";
	
	this->previous[2] = 0;
	this->next[2] = 0;
	this->result[2] = 0;
	this->method[2] = "method not specified";
	
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
	
	return this->result[this->call++];
}

void Link_create(struct Link * this, size_t place, size_t origin, size_t destination)
{

}

void Link_read(struct Link * this, size_t place)
{
	this->method[this->call] = "Link_read";
	this->call++;
}

void Link_joinOutgoing(struct Link * this, size_t previous, size_t next)
{

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

}

void Link_shiftIncoming(struct Link * this, size_t previous)
{
	this->previous[this->call] = previous;
	this->method[this->call] = "Link_shiftIncoming";
	this->call++;
}

char Link_isOutgoingToNode(struct Link * this, size_t destination)
{
	return 0;
}

char Link_isIncomingFromNode(struct Link * this, size_t origin)
{
	return 0;
}

size_t Link_getNextOutgoing(struct Link * this)
{
	return 0;
}

size_t Link_getNextIncoming(struct Link * this)
{
	return 0;
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
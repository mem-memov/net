#include "../source/Net.h"

#define NET_MAX_CALLS 3

struct Net
{
	char call;
	char * method[NET_MAX_CALLS];
	size_t placeSize[NET_MAX_CALLS];
	size_t place[NET_MAX_CALLS];
	char hasCreatedEntry[NET_MAX_CALLS];
	char canCreateEntry[NET_MAX_CALLS];
	size_t size[NET_MAX_CALLS];
	struct Stream * stream[NET_MAX_CALLS];
	size_t graphSize[NET_MAX_CALLS];
};

struct Net * Net_mock()
{
	struct Net * this = malloc(sizeof(struct Net));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < NET_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->placeSize[i] = 55555;
		this->place[i] = 55555;
		this->hasCreatedEntry[i] = 27;
		this->canCreateEntry[i] = 27;
		this->size[i] = 55555;
		this->stream[i] = NULL;
		this->graphSize[i] = 55555;		
	}

	return this;
}

void Net_destruct(struct Net * this)
{
	free(this);
	this = NULL;
}

void Net_create(struct Net * this, size_t placeSize)
{
	this->method[this->call] = "Net_create";
	this->placeSize[this->call] = placeSize;
	
	this->call++;
}

void Net_read(struct Net * this)
{
	this->method[this->call] = "Net_read";
	
	this->call++;
}

char Net_hasEntry(struct Net * this, size_t place)
{
	this->method[this->call] = "Net_hasEntry";
	this->place[this->call] = place;
	
	char hasCreatedEntry = this->hasCreatedEntry[this->call];
	
	this->call++;
	
	return hasCreatedEntry;
}

char Net_canCreateEntry(struct Net * this)
{
	this->method[this->call] = "Net_canCreateEntry";
	
	char canCreateEntry = this->canCreateEntry[this->call];
	
	this->call++;
	
	return canCreateEntry;
}

size_t Net_createEntry(struct Net * this)
{
	this->method[this->call] = "Net_createEntry";
	
	size_t place = this->place[this->call];
	
	this->call++;
	
	return place;
}

void Net_deleteEntry(struct Net * this, size_t place)
{
	this->method[this->call] = "Net_deleteEntry";
	this->place[this->call] = place;

	this->call++;
}

size_t Net_calculateSize(struct Net * this)
{
	this->method[this->call] = "Net_calculateSize";
	
	size_t size = this->size[this->call];
	
	this->call++;
	
	return size;
}

void Net_import(struct Net * this, struct Stream * stream, size_t graphSize)
{
	this->method[this->call] = "Net_import";
	this->stream[this->call] = stream;
	this->graphSize[this->call] = graphSize;

	this->call++;
}
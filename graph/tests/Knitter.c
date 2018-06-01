#include "../source/Knitter.h"

#define KNITTER_MAX_CALLS 3

struct Knitter
{
	char call;
	char * method[KNITTER_MAX_CALLS];
	size_t placeSize[KNITTER_MAX_CALLS];
	size_t place[KNITTER_MAX_CALLS];
	char hasCreatedEntry[KNITTER_MAX_CALLS];
	char canCreateEntry[KNITTER_MAX_CALLS];
	size_t size[KNITTER_MAX_CALLS];
	struct Stream * stream[KNITTER_MAX_CALLS];
	size_t graphSize[KNITTER_MAX_CALLS];
};

struct Knitter * Knitter_mock()
{
	struct Knitter * this = malloc(sizeof(struct Knitter));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < KNITTER_MAX_CALLS; i++) {
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

void Knitter_destruct(struct Knitter * this)
{
	free(this);
	this = NULL;
}

void Knitter_create(struct Knitter * this, size_t placeSize)
{
	this->method[this->call] = "Knitter_create";
	this->placeSize[this->call] = placeSize;
	
	this->call++;
}

void Knitter_read(struct Knitter * this)
{
	this->method[this->call] = "Knitter_read";
	
	this->call++;
}

char Knitter_hasCreatedEntry(struct Knitter * this, size_t place)
{
	this->method[this->call] = "Knitter_hasCreatedEntry";
	this->place[this->call] = place;
	
	char hasCreatedEntry = this->hasCreatedEntry[this->call];
	
	this->call++;
	
	return hasCreatedEntry;
}

char Knitter_canCreateEntry(struct Knitter * this)
{
	this->method[this->call] = "Knitter_canCreateEntry";
	
	char canCreateEntry = this->canCreateEntry[this->call];
	
	this->call++;
	
	return canCreateEntry;
}

size_t Knitter_createEntry(struct Knitter * this)
{
	this->method[this->call] = "Knitter_createEntry";
	
	size_t place = this->place[this->call];
	
	this->call++;
	
	return place;
}

void Knitter_deleteEntry(struct Knitter * this, size_t place)
{
	this->method[this->call] = "Knitter_deleteEntry";
	this->place[this->call] = place;

	this->call++;
}

size_t Knitter_calculateSize(struct Knitter * this)
{
	this->method[this->call] = "Knitter_calculateSize";
	
	size_t size = this->size[this->call];
	
	this->call++;
	
	return size;
}

void Knitter_import(struct Knitter * this, struct Stream * stream, size_t graphSize)
{
	this->method[this->call] = "Knitter_import";
	this->stream[this->call] = stream;
	this->graphSize[this->call] = graphSize;

	this->call++;
}
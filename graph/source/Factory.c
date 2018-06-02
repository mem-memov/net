#include "Factory.h"
#include <stdlib.h>
#include "Counts.h"
#include "Errors.h"
#include "Exports.h"
#include "Imports.h"
#include "Nets.h"
#include "Links.h"
#include "Boats.h"
#include "Nodes.h"
#include "Places.h"
#include "Spaces.h"
#include "Stars.h"
#include "Streams.h"
#include "Telescopes.h"

struct Factory
{
	size_t graphSize;
	size_t entrySize;
	size_t placeSize;
	
	unsigned char * bytes;
	
	struct Streams * streams;
	struct Counts * counts;
	struct Errors * errors;
	struct Links * links;
	struct Boats * boats;
	struct Nodes * nodes;
	struct Places * places;
	struct Stars * stars;
	struct Imports * imports;
};

struct Factory * Factory_construct(
	unsigned char * bytes, 
	size_t graphSize, 
	size_t entrySize, 
	size_t placeSize
) {
	struct Factory * this = malloc(sizeof(struct Factory));

	this->graphSize = graphSize;
	this->entrySize = entrySize;
	this->placeSize = placeSize;
	
	this->bytes = bytes;
	
	this->errors = Errors_construct(Error_construct());
	this->places = Places_construct(this->placeSize, this->bytes);
	
	this->streams = Streams_construct(this->bytes);
	
	this->counts = Counts_construct(
		this->places, 
		Errors_makeCountError(this->errors)
	);
	
	this->boats = Boats_construct(
		this->places, 
		this->counts, 
		Nets_construct(
			Meshes_construct(
				Gaps_construct(this->places)
			),
			this->places,
			Spaces_construct(graphSize, this->entrySize, this->placeSize),
			Errors_makeNetError(this->errors)
		),
		Exports_construct(this->streams),
		Errors_makeBoatError(this->errors)
	);
	
	this->links = Links_construct(
		Errors_makeLinkError(this->errors), 
		Directions_construct(
			this->places, 
			Errors_makeDirectionError(this->errors)
		)
	);

	this->stars = Stars_construct(
		this->links,
		Telescopes_construct(
			this->links
		),
		Errors_makeStarError(this->errors)
	);
	
	this->nodes = Nodes_construct(
		this->places, 
		this->counts, 
		this->stars, 
		Errors_makeNodeError(this->errors)
	);

	return this;
}

void Factory_destruct(struct Factory * this)
{
	Counts_destruct(this->counts);
	Boats_destruct(this->boats);
	Stars_destruct(this->stars);
	Links_destruct(this->links);
	Nodes_destruct(this->nodes);
	Places_destruct(this->places);
	Errors_destruct(this->errors);
	
	Imports_destruct(this->imports);
	Streams_destruct(this->streams);
	
	free(this);
	this = NULL;
}

struct Boat * Factory_makeBoat(struct Factory * this)
{
	return Boats_make(this->boats, this->graphSize, this->entrySize, this->placeSize);
}

struct Import * Factory_makeImport(struct Factory * this)
{
	return Imports_make(this->imports);
}

struct Link * Factory_makeLink(struct Factory * this)
{
	return Links_make(this->links);
}

struct Node * Factory_makeNode(struct Factory * this)
{
	return Nodes_make(this->nodes);
}
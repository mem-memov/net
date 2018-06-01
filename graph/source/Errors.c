#include "Errors.h"
#include <stdlib.h>

struct Errors
{
	struct Error * error;
	struct CountError * countError;
	struct DirectionError * directionError;
	struct KnitterError * knitterError;
	struct LinkError * linkError;
	struct BoatError * boatError;
	struct NodeError * nodeError;
	struct StarError * starError;
};

struct Errors * Errors_construct(struct Error * error)
{
	struct Errors * this = malloc(sizeof(struct Errors));
	
	this->error = error;
	
	this->countError = NULL;
	this->directionError = NULL;
	this->knitterError = NULL;
	this->linkError = NULL;
	this->boatError = NULL;
	this->nodeError = NULL;
	this->starError = NULL;
	
	return this;
}

void Errors_destruct(struct Errors * this)
{
	if (NULL != this->countError) {
		CountError_destruct(this->countError);
	}
	if (NULL != this->directionError) {
		DirectionError_destruct(this->directionError);
	}
	if (NULL != this->knitterError) {
		KnitterError_destruct(this->knitterError);
	}
	if (NULL != this->linkError) {
		LinkError_destruct(this->linkError);
	}
	if (NULL != this->boatError) {
		BoatError_destruct(this->boatError);
	}
	if (NULL != this->nodeError) {
		NodeError_destruct(this->nodeError);
	}
	if (NULL != this->starError) {
		StarError_destruct(this->starError);
	}
	Error_destruct(this->error);
	
	free(this);
	this = NULL;
}

struct CountError * Errors_makeCountError(struct Errors * this)
{
	if (NULL == this->countError) {
		this->countError = CountError_construct(this->error);
	}
	
	return this->countError;
}

struct DirectionError * Errors_makeDirectionError(struct Errors * this)
{
	if (NULL == this->directionError) {
		this->directionError = DirectionError_construct(this->error);
	}
	
	return this->directionError;
}

struct KnitterError * Errors_makeKnitterError(struct Errors * this)
{
	if (NULL == this->knitterError) {
		this->knitterError = KnitterError_construct(this->error);
	}
	
	return this->knitterError;
}

struct LinkError * Errors_makeLinkError(struct Errors * this)
{
	if (NULL == this->linkError) {
		this->linkError = LinkError_construct(this->error);
	}
	
	return this->linkError;
}

struct BoatError * Errors_makeBoatError(struct Errors * this)
{
	if (NULL == this->boatError) {
		this->boatError = BoatError_construct(this->error);
	}
	
	return this->boatError;
}

struct NodeError * Errors_makeNodeError(struct Errors * this)
{
	if (NULL == this->nodeError) {
		this->nodeError = NodeError_construct(this->error);
	}
	
	return this->nodeError;
}

struct StarError * Errors_makeStarError(struct Errors * this)
{
	if (NULL == this->starError) {
		this->starError = StarError_construct(this->error);
	}
	
	return this->starError;
}
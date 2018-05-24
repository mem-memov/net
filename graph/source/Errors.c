#include "Errors.h"
#include <stdlib.h>

struct Errors
{
	struct Error * error;
	struct CountError * countError;
	struct DirectionError * directionError;
	struct LinkError * linkError;
	struct NodeError * nodeError;
};

struct Errors * Errors_construct(struct Error * error)
{
	struct Errors * this = malloc(sizeof(struct Errors));
	
	this->error = error;
	
	this->countError = NULL;
	this->directionError = NULL;
	this->linkError = NULL;
	this->nodeError = NULL;
	
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
	if (NULL != this->linkError) {
		LinkError_destruct(this->linkError);
	}
	if (NULL != this->nodeError) {
		NodeError_destruct(this->nodeError);
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

struct LinkError * Errors_makeLinkError(struct Errors * this)
{
	if (NULL == this->linkError) {
		this->linkError = LinkError_construct(this->error);
	}
	
	return this->linkError;
}

struct NodeError * Errors_makeNodeError(struct Errors * this)
{
	if (NULL == this->nodeError) {
		this->nodeError = NodeError_construct(this->error);
	}
	
	return this->nodeError;
}
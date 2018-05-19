#include "Application.h"
#include "Request.h"
#include "Response.h"
#include "Error.h"
#include <ndb.h>
#include <stdlib.h>

struct Application {
    int bufferLength;
};

struct Application * Application_construct(int bufferLength)
{
	struct Application * this = malloc(sizeof(struct Application));

	this->bufferLength = bufferLength;

	return this;
}

void Application_destruct(struct Application * this)
{
    free(this);
	this = NULL;
}

static void Application_create(struct Application * this, struct Request * request, struct Response * response)
{
    long int id = ndb_create();
    Response_addNumber(response, id);
}

static void Application_read(struct Application * this, struct Request * request, struct Response * response)
{
    long int nodeId = Request_getArgument(request, 1);
    long int buffer[this->bufferLength];
    long int total = ndb_read(nodeId, buffer, this->bufferLength);

    Error_inApplicationWhileExecutingWithSmallBuffer(this->bufferLength, total);

    Response_addNumbers(response, buffer, this->bufferLength, total);
}

static void Application_connect(struct Application * this, struct Request * request, struct Response * response)
{
    long int fromNodeId = Request_getArgument(request, 1);
    long int toNodeId = Request_getArgument(request, 2);
    ndb_connect(fromNodeId, toNodeId);
}

static void Application_intersect(struct Application * this, struct Request * request, struct Response * response)
{
    long int nodeCount = Request_countArguments(request);
    long int nodeIds[nodeCount];
    Request_getArguments(request, nodeIds, nodeCount);
    long int buffer[this->bufferLength];
    long int total = ndb_intersect(nodeIds, nodeCount, buffer, this->bufferLength);

    Error_inApplicationWhileExecutingWithSmallBuffer(this->bufferLength, total);

    Response_addNumbers(response, buffer, this->bufferLength, total);
}

static void Application_union(struct Application * this, struct Request * request, struct Response * response)
{
    long int nodeCount = Request_countArguments(request);
    long int nodeIds[nodeCount];
    Request_getArguments(request, nodeIds, nodeCount);
    long int buffer[this->bufferLength];
    long int total = ndb_union(nodeIds, nodeCount, buffer, this->bufferLength);

    Error_inApplicationWhileExecutingWithSmallBuffer(this->bufferLength, total);

    Response_addNumbers(response, buffer, this->bufferLength, total);
}

static void Application_difference(struct Application * this, struct Request * request, struct Response * response)
{
    long int nodeCount = Request_countArguments(request);
    long int nodeIds[nodeCount];
    Request_getArguments(request, nodeIds, nodeCount);
    long int buffer[this->bufferLength];
    long int total = ndb_difference(nodeIds, nodeCount, buffer, this->bufferLength);

    Error_inApplicationWhileExecutingWithSmallBuffer(this->bufferLength, total);

    Response_addNumbers(response, buffer, this->bufferLength, total);
}

static void Application_insiders(struct Application * this, struct Request * request, struct Response * response)
{
    long int nodeCount = Request_countArguments(request);
    Error_inApplicationWhileExecutingWithFewArguments(nodeCount, 2);
    long int nodeIds[nodeCount];
    Request_getArguments(request, nodeIds, nodeCount);
    long int buffer[this->bufferLength];
    long int total = ndb_insiders(nodeIds[0], nodeIds+1, nodeCount-1, buffer, this->bufferLength);

    Error_inApplicationWhileExecutingWithSmallBuffer(this->bufferLength, total);

    Response_addNumbers(response, buffer, this->bufferLength, total);
}

static void Application_outsiders(struct Application * this, struct Request * request, struct Response * response)
{
    long int nodeCount = Request_countArguments(request);
    Error_inApplicationWhileExecutingWithFewArguments(nodeCount, 2);
    long int nodeIds[nodeCount];
    Request_getArguments(request, nodeIds, nodeCount);
    long int buffer[this->bufferLength];
    long int total = ndb_outsiders(nodeIds[0], nodeIds+1, nodeCount-1, buffer, this->bufferLength);

    Error_inApplicationWhileExecutingWithSmallBuffer(this->bufferLength, total);

    Response_addNumbers(response, buffer, this->bufferLength, total);
}

void Application_execute(struct Application * this, struct Request * request, struct Response * response)
{
    if (1 == Request_isCommand(request, "create"))
    {
        Application_create(application, request, response);
    }
    else if (1 == Request_isCommand(request, "read"))
    {
        Application_read(application, request, response);
    }
    else if (1 == Request_isCommand(request, "connect"))
    {
        Application_connect(application, request, response);
    }
    else if (1 == Request_isCommand(request, "intersect"))
    {
        Application_intersect(application, request, response);
    }
    else if (1 == Request_isCommand(request, "union"))
    {
        Application_union(application, request, response);
    }
    else if (1 == Request_isCommand(request, "difference"))
    {
        Application_difference(application, request, response);
    }
    else if (1 == Request_isCommand(request, "insiders"))
    {
        Application_insiders(application, request, response);
    }
    else if (1 == Request_isCommand(request, "outsiders"))
    {
        Application_outsiders(application, request, response);
    }
    else
    {
        Error_inApplicationWhileExecutingWithUnknownCommand();
    }
}

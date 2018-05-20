#include "Application.h"
#include "Request.h"
#include "Response.h"
#include "Error.h"
#include <netdatabase.h>
#include <stdlib.h>

struct Application {
    int bufferLength;
	struct Database * database;
};

struct Application * Application_construct(int bufferLength)
{
	struct Application * this = malloc(sizeof(struct Application));

	this->bufferLength = bufferLength;
	
	this->database = Database_construct();

	return this;
}

void Application_destruct(struct Application * this)
{
    free(this);
	this = NULL;
}

static void Application_create(struct Application * this, struct Request * request, struct Response * response)
{
//	size_t id = Graph_addNode(this->graph);
//	Response_addNumber(response, id);
}

static void Application_read(struct Application * this, struct Request * request, struct Response * response)
{
//    long int nodeId = Request_getArgument(request, 1);
//	
//	long int * buffer;
//	long int total;
//	
//	Graph_getNodeDestinations(this->graph, nodeId, &buffer, &total);
//
//    Error_inApplicationWhileExecutingWithSmallBuffer(this->bufferLength, total);
//
//	Response_addNumbers(response, buffer, this->bufferLength, total);
}

static void Application_connect(struct Application * this, struct Request * request, struct Response * response)
{
//    long int fromNodeId = Request_getArgument(request, 1);
//    long int toNodeId = Request_getArgument(request, 2);
//	Graph_connectNodes(this->graph, fromNodeId, toNodeId);
}

static void Application_intersect(struct Application * this, struct Request * request, struct Response * response)
{
//    long int nodeCount = Request_countArguments(request);
//    long int nodeIds[nodeCount];
//    Request_getArguments(request, nodeIds, nodeCount);
//    long int buffer[this->bufferLength];
//    long int total = ndb_intersect(nodeIds, nodeCount, buffer, this->bufferLength);
//
//    Error_inApplicationWhileExecutingWithSmallBuffer(this->bufferLength, total);
//
//    Response_addNumbers(response, buffer, this->bufferLength, total);
}

static void Application_union(struct Application * this, struct Request * request, struct Response * response)
{
//    long int nodeCount = Request_countArguments(request);
//    long int nodeIds[nodeCount];
//    Request_getArguments(request, nodeIds, nodeCount);
//    long int buffer[this->bufferLength];
//    long int total = ndb_union(nodeIds, nodeCount, buffer, this->bufferLength);
//
//    Error_inApplicationWhileExecutingWithSmallBuffer(this->bufferLength, total);
//
//    Response_addNumbers(response, buffer, this->bufferLength, total);
}

static void Application_difference(struct Application * this, struct Request * request, struct Response * response)
{
//    long int nodeCount = Request_countArguments(request);
//    long int nodeIds[nodeCount];
//    Request_getArguments(request, nodeIds, nodeCount);
//    long int buffer[this->bufferLength];
//    long int total = ndb_difference(nodeIds, nodeCount, buffer, this->bufferLength);
//
//    Error_inApplicationWhileExecutingWithSmallBuffer(this->bufferLength, total);
//
//    Response_addNumbers(response, buffer, this->bufferLength, total);
}

static void Application_insiders(struct Application * this, struct Request * request, struct Response * response)
{
//    long int nodeCount = Request_countArguments(request);
//    Error_inApplicationWhileExecutingWithFewArguments(nodeCount, 2);
//    long int nodeIds[nodeCount];
//    Request_getArguments(request, nodeIds, nodeCount);
//    long int buffer[this->bufferLength];
//    long int total = ndb_insiders(nodeIds[0], nodeIds+1, nodeCount-1, buffer, this->bufferLength);
//
//    Error_inApplicationWhileExecutingWithSmallBuffer(this->bufferLength, total);
//
//    Response_addNumbers(response, buffer, this->bufferLength, total);
}

static void Application_outsiders(struct Application * this, struct Request * request, struct Response * response)
{
//    long int nodeCount = Request_countArguments(request);
//    Error_inApplicationWhileExecutingWithFewArguments(nodeCount, 2);
//    long int nodeIds[nodeCount];
//    Request_getArguments(request, nodeIds, nodeCount);
//    long int buffer[this->bufferLength];
//    long int total = ndb_outsiders(nodeIds[0], nodeIds+1, nodeCount-1, buffer, this->bufferLength);
//
//    Error_inApplicationWhileExecutingWithSmallBuffer(this->bufferLength, total);
//
//    Response_addNumbers(response, buffer, this->bufferLength, total);
}

void Application_execute(struct Application * this, struct Request * request, struct Response * response)
{
//    if (1 == Request_isCommand(request, "create"))
//    {
//        Application_create(this, request, response);
//    }
//    else if (1 == Request_isCommand(request, "read"))
//    {
//        Application_read(this, request, response);
//    }
//    else if (1 == Request_isCommand(request, "connect"))
//    {
//        Application_connect(this, request, response);
//    }
//    else if (1 == Request_isCommand(request, "intersect"))
//    {
//        Application_intersect(this, request, response);
//    }
//    else if (1 == Request_isCommand(request, "union"))
//    {
//        Application_union(this, request, response);
//    }
//    else if (1 == Request_isCommand(request, "difference"))
//    {
//        Application_difference(this, request, response);
//    }
//    else if (1 == Request_isCommand(request, "insiders"))
//    {
//        Application_insiders(this, request, response);
//    }
//    else if (1 == Request_isCommand(request, "outsiders"))
//    {
//        Application_outsiders(this, request, response);
//    }
//    else
//    {
//        Error_inApplicationWhileExecutingWithUnknownCommand();
//    }
}

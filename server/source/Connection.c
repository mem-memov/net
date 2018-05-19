#include "Connection.h"
#include "Request.h"
#include "Response.h"
#include "Error.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

struct Connection {
    int descriptor;
    struct Request * request;
    struct Response * response;
};

struct Connection * Connection_construct(int descriptor, struct Request * request, struct Response * response)
{
	struct Connection * this = malloc(sizeof(struct Connection));

	this->descriptor = descriptor;
	this->request = request;
	this->response = response;

	return this;
}

void Connection_destruct(struct Connection * this)
{
    Request_destruct(this->request);
    Response_destruct(this->response);
    free(this);
	this = NULL;
}

struct Request * Connection_request(struct Connection * this)
{
    return this->request;
}

struct Response * Connection_response(struct Connection * this)
{
    return this->response;
}

void Connection_close(struct Connection * this)
{
    close(this->descriptor);
}

void Connection_receive(struct Connection * this)
{
    Request_clean(this->request);
    Response_clean(this->response);

    int receivedLength;
    int availableLength = Request_maxLength(this->request) - 1; // string end

    do {
        receivedLength = recv(this->descriptor, Request_body(this->request), availableLength, 0);
        availableLength -= receivedLength;
        Error_inConnectionWhileReceiving(availableLength);
    }
    while (receivedLength > 0 && 0 == Request_isFinished(this->request));
}

void Connection_send(struct Connection * this)
{
    int sendResult = send(this->descriptor, Response_body(this->response), Response_length(this->response), 0);
    Error_inConnectionAfterSending(sendResult);

    Request_clean(this->request);
    Response_clean(this->response);
}

char Connection_mustClose(struct Connection * this)
{
    if (1 == Request_isCommand(this->request, "exit"))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char Connection_isIdle(struct Connection * this)
{
    return Request_isEmpty(this->request);
}

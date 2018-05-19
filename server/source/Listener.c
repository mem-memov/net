#include "Listener.h"
#include "Connection.h"
#include "Request.h"
#include "Response.h"
#include "Error.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

struct Listener {
    int port;
    int connectionLimit;
    int descriptor;
};

struct Listener * Listener_construct(int port, int connectionLimit)
{
	struct Listener * this = malloc(sizeof(struct Listener));

	this->port = port;
	this->connectionLimit = connectionLimit;
	this->descriptor = -2;

	return this;
}

void Listener_destruct(struct Listener * this)
{
    free(this);
	this = NULL;
}

void Listener_open(struct Listener * this)
{
    Error_inListenerBeforeOpeningSocket(this->descriptor);

    this->descriptor = socket(PF_INET, SOCK_STREAM, 0);

    Error_inListenerAfterOpeningSocket(this->descriptor);
}

void Listener_bind(struct Listener * this)
{
    Error_inListenerBeforeBindingToPort(this->descriptor);

    int reuse = 1;

    int setSocketOptionResult = setsockopt(this->descriptor, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int));

    Error_inListenerAfterSettingSocketOption(setSocketOptionResult);

    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(this->port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    int bindResult = bind(this->descriptor, (struct sockaddr *)&name, sizeof(name));

    Error_inListenerAfterBindingToPort(bindResult);
}

void Listener_listen(struct Listener * this)
{
    Error_inListenerBeforeListening(this->descriptor);

    int listenResult = listen(this->descriptor, this->connectionLimit);

    Error_inListenerAfterListening(listenResult);
}

struct Connection * Listener_accept(struct Listener * this, int bufferLength)
{
    Error_inListenerBeforeAcceptingConnection(this->descriptor);

    struct sockaddr_storage clientAddress;
    unsigned int clientAddressSize = sizeof(clientAddress);
    int connectionDescriptor = accept(this->descriptor, (struct sockaddr *)&clientAddress, &clientAddressSize);

    Error_inListenerAfterAcceptingConnection(connectionDescriptor);

    struct Request * request = Request_construct(bufferLength);
    struct Response * response = Response_construct(bufferLength);
    struct Connection * connection = Connection_construct(connectionDescriptor, request, response);

    return connection;
}

void Listener_close(struct Listener * this)
{
    close(this->descriptor);
    this->descriptor = -2;
}

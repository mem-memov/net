#include "Help.h"
#include <stdlib.h>
#include <stdio.h>

struct Help
{
	//
};

struct Help * Help_construct()
{
	struct Help * this = malloc(sizeof(struct Help));

	return this;
}

void Help_destruct(struct Help * this)
{
	free(this);
	this = NULL;
}

void Help_printCommandLineManual(struct Help * this)
{
	printf("-p --port			The port of the server.\n");
	printf("-c --connections	The maximum number of connections in queue waiting for server response.\n");
	printf("-b --buffer			The size of buffers storing request and response strings. Given in bytes.\n");
	printf("-t --threads		The number of workers the server spawns as separate threads in order to handle incoming requests.\n");
}

void Help_printStatus(struct Help * this, int port, int connectionLimit, int bufferLength, int threadNumber)
{
    printf("Node Database Server is running:\n");
    printf(" port: %d.\n", port);
    printf(" maximum connections: %d\n", connectionLimit);
    printf(" buffer size: %d bytes\n", bufferLength);
    printf(" thread number: %d\n", threadNumber);
    printf("Commands:\n");
    printf(" exit\n");
    printf("Source code:");
    printf(" https://github.com/mem-memov/net\n");
    printf("Press Ctrl+C to stop this server.\n");
}
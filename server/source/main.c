#include "Server.h"
#include "Signal.h"
#include "Application.h"
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

struct Server * server = NULL;

void handleShutDown()
{
    if (NULL != server)
    {
        Server_stop(server);
        Server_destruct(server);
    }

    exit(0);
}

void printHelp(int port, int connectionLimit, int bufferLength, int threadNumber);

int main(int argc, char *argv[])
{
	int port;
	int connectionLimit;
	int bufferLength;
	int threadNumber;
	
	int opt = 0;
	
    const char * short_options = "pcbt";

    const struct option long_options[] = {
        {"port", required_argument, &port, 43152},
        {"connection-limit", required_argument, &connectionLimit, 10},
        {"buffer-length", required_argument, &bufferLength, 8192},
        {"thread-number", required_argument, &threadNumber, 4},
        {NULL,0,NULL,0}
    };

    while (opt = getopt_long(argc, argv, short_options, long_options, NULL) != -1) {
		switch (opt) {
			case 'p' : 
				port = (int)strtol(optarg, NULL, 10);
				break;
			case 'c' : 
				connectionLimit = (int)strtol(optarg, NULL, 10);
				break;
			case 'b' : 
				bufferLength = (int)strtol(optarg, NULL, 10);
				break;
			case 't' : 
				threadNumber = (int)strtol(optarg, NULL, 10);
				break;
			default:
				printf("unknown flag");
				exit(EXIT_FAILURE);
		}
	}

    struct Signal * sigint = Signal_constructSigint(handleShutDown);
    Signal_catch(sigint);

    struct Application * application = Application_construct(bufferLength);

    server = Server_construct(port, connectionLimit, bufferLength, threadNumber, application);

    printHelp(port, connectionLimit, bufferLength, threadNumber);
    Server_start(server);

    return(0);
}

void printHelp(int port, int connectionLimit, int bufferLength, int threadNumber)
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

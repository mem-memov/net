#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Error.h"
#include "Net.h"

int main(int argc, char** argv) {
	
	struct Error * error = Error_construct();
	struct Net * net = Net_construct(5, error);

	char command[100];
	unsigned int place;
	struct Node * node;
	struct Node * originNode;
	struct Node * destinationNode;
	char filePath[300];
	FILE * file;

	while (1) {
		printf( "Enter a command:");
		scanf("%s", command);
		printf("You entered: %s\n", command);
		
		if (strcmp("create", command) == 0 || strcmp("+", command) == 0) {

			if ( ! Net_canAddNode(net)) {
				printf("No space for new nodes.\n");
			} else {
				node = Net_addNode(net);
				printf("Node created: %d\n", Node_getPlace(node));
			}

			continue;
		}

		if (strcmp("connect", command) == 0 || strcmp("^", command) == 0) {
			
			printf( "origin node:");
			scanf("%u", &place);
			
			originNode = Net_getNode(net, place);
			
			printf( "destination node:");
			scanf("%u", &place);
			
			destinationNode = Net_getNode(net, place);
			
			Node_connect(originNode, destinationNode);
			
			continue;
		}

		if (strcmp("read", command) == 0 || strcmp(":", command) == 0) {
			
			printf( "node:");
			scanf("%u", &place);
			
			node = Net_getNode(net, place);
			
			Node_export(node, stdout);
			
			continue;
		}

		if (strcmp("export", command) == 0 || strcmp(">>", command) == 0) {

			printf( "target file path:");
			scanf("%s", filePath);

			file = fopen(filePath, "w+");
			Net_export(net, file);
			fclose(file);
			
			continue;
		}

		if (strcmp("show", command) == 0 || strcmp(">", command) == 0) {

			Net_export(net, stdout);
			
			continue;
		}

		if (strcmp("exit", command) == 0 || strcmp("q", command) == 0) {
			break;
		}
		
		printf( "Unknown command '%s'. Enter 'exit' to stop execution.\n", command);
   }

   return (EXIT_SUCCESS);
}


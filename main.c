#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Net.h"

int main(int argc, char** argv) {

	struct Net * net = Net_construct(
		Space_construct(12)
	);

	char command[100];
	unsigned int nodePlace;

	while (1) {
		scanf("%s", command);
		
		if (strcmp("create", command) == 0 || strcmp("+", command) == 0) {
			
			if (! Net_canAddNode(net)) {
				printf("No space for new nodes.\n");
			} else {
				struct Node * node = Net_addNode(net);
				printf("Node created: %d\n", Node_getPlace(node));
			}

			continue;
		}

		if (strcmp("connect", command) == 0 || strcmp(">", command) == 0) {
			
			scanf("%u", &nodePlace);
			
			struct Node * originNode = Net_getNode(net, nodePlace);
			
			scanf("%u", &nodePlace);
			
			struct Node * destinationNode = Net_getNode(net, nodePlace);
			
			Node_connect(originNode, destinationNode);
			
			continue;
		}

		if (strcmp("exit", command) == 0) {
			break;
		}
		
		printf( "Unknown command '%s'. Enter 'exit' to stop execution.\n", command);
   }

   return (EXIT_SUCCESS);
}


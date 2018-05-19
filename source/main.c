#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

int main(int argc, char** argv) {
	
	struct Graph * graph = Graph_construct(100);

	char command[100];
	size_t place;
	size_t origin;
	size_t destination;
	size_t * nodes;
	size_t length;
	size_t i;
	char filePath[300];
	FILE * file;

	while (1) {
		printf("Enter a command: ");
		scanf("%s", command);
		
		if (strcmp("create", command) == 0 || strcmp("*", command) == 0) {

			if ( ! Graph_hasFreePlace(graph)) {
				printf("No graph for new nodes.\n");
			} else {
				place = Graph_addNode(graph);
				printf("Node created: %zu\n", place);
			}

			continue;
		}

		if (strcmp("remove", command) == 0 || strcmp(".", command) == 0) {

			printf("node: ");
			scanf("%zu", &place);

			if ( ! Graph_isNode(graph, place)) {
				printf("%zu is not a node\n", place);
				continue;
			}
			
			Graph_removeNode(graph, place);

			continue;
		}

		if (strcmp("connect", command) == 0 || strcmp("+", command) == 0) {
			
			printf("origin node:");
			scanf("%zu", &origin);
			
			if ( ! Graph_isNode(graph, origin)) {
				printf("%zu is not a node\n", origin);
				continue;
			}

			printf("destination node:");
			scanf("%zu", &destination);
			
			if ( ! Graph_isNode(graph, destination)) {
				printf("%zu is not a node\n", destination);
				continue;
			}

			Graph_connectNodes(graph, origin, destination);
			
			continue;
		}

		if (strcmp("disconnect", command) == 0 || strcmp("-", command) == 0) {
			
			printf("origin node:");
			scanf("%zu", &origin);
			
			if ( ! Graph_isNode(graph, origin)) {
				printf("%zu is not a node\n", origin);
				continue;
			}

			printf("destination node:");
			scanf("%zu", &destination);
			
			if ( ! Graph_isNode(graph, destination)) {
				printf("%zu is not a node\n", destination);
				continue;
			}

			Graph_disconnectNodes(graph, origin, destination);
			
			continue;
		}

		if (strcmp("read", command) == 0 || strcmp(":", command) == 0) {
			
			printf("node: ");
			scanf("%zu", &place);

			if ( ! Graph_isNode(graph, place)) {
				printf("%zu is not a node\n", place);
				continue;
			}

			Graph_getNodeDestinations(graph, place, &nodes, &length);
			for (i = 0; i < length; i++) {
				printf("%zu\n", nodes[i]);
			}
			free(nodes);
			nodes = NULL;

			continue;
		}


		if (strcmp("delete", command) == 0 || strcmp("x", command) == 0) {
			
			printf("node: ");
			scanf("%zu", &place);

			if ( ! Graph_isNode(graph, place)) {
				printf("%zu is not a node\n", place);
				continue;
			}
			
			Graph_removeNode(graph, place);
			
			continue;
		}

		if (strcmp("export", command) == 0 || strcmp(">", command) == 0) {

			printf( "destination file path:");
			scanf("%s", filePath);

			file = fopen(filePath, "wb");
			Graph_export(graph, file);
			fclose(file);
			
			continue;
		}

		if (strcmp("import", command) == 0 || strcmp("<", command) == 0) {

			printf( "source file path:");
			scanf("%s", filePath);

			file = fopen(filePath, "rb");
			Graph_import(graph, file);
			fclose(file);
			
			continue;
		}

		if (strcmp("exit", command) == 0 || strcmp("q", command) == 0) {
			Graph_destruct(graph);
			break;
		}
		
		printf( "Unknown command '%s'. Enter 'exit' to stop execution.\n", command);
   }

   return (EXIT_SUCCESS);
}


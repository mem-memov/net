#ifndef ERROR_H
#define ERROR_H

struct Error {
	//
};

struct Error * Error_construct();

void Error_destruct(struct Error * error);

void Error_netHasNoSpaceLeft(char hasSpaceForNodes);

void Error_netHasNoSuchNode(char hasNode, unsigned int place);

#endif
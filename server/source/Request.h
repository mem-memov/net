#ifndef REQUEST_HEADER
#define REQUEST_HEADER

struct Request;

struct Request * Request_construct(int maxLength);

void Request_destruct(struct Request * this);

char * Request_body(struct Request * this);

void Request_clean(struct Request * this);

int Request_maxLength(struct Request * this);

char Request_isFinished(struct Request * this);

char Request_isCommand(struct Request * this, char * command);

long int Request_getArgument(struct Request * this, int orderNumber);

long int Request_countArguments(struct Request * this);

void Request_getArguments(struct Request * this, long int * arguments, long int length);

char Request_isEmpty(struct Request * this);

#endif

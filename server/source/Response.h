#ifndef RESPONSE_HEADER
#define RESPONSE_HEADER

struct Response;

struct Response * Response_construct(int maxLength);

void Response_destruct(struct Response * this);

char * Response_body(struct Response * this);

int Response_length(struct Response * this);

void Response_clean(struct Response * this);

void Response_addNumber(struct Response * this, long int number);

void Response_addNumbers(struct Response * this, long int * buffer, long int bufferLength, long int total);

#endif

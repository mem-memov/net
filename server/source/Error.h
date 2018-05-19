#ifndef ERROR_HEADER
#define ERROR_HEADER

void Error_inApplicationWhileExecutingWithSmallBuffer(int bufferLength, long int total);
void Error_inApplicationWhileExecutingWithUnknownCommand();
void Error_inApplicationWhileExecutingWithFewArguments(long int actual, char minimum);

void Error_inConnectionWhileReceiving(int availableBufferLength);
void Error_inConnectionAfterSending(int sendResult);

void Error_inListenerBeforeOpeningSocket(int listenerDescriptor);
void Error_inListenerAfterOpeningSocket(int listenerDescriptor);
void Error_inListenerBeforeBindingToPort(int listenerDescriptor);
void Error_inListenerAfterSettingSocketOption(int setSocketOptionResult);
void Error_inListenerAfterBindingToPort(int bindResult);
void Error_inListenerBeforeListening(int listenerDescriptor);
void Error_inListenerAfterListening(int listenResult);
void Error_inListenerBeforeAcceptingConnection(int listenerDescriptor);
void Error_inListenerAfterAcceptingConnection(int connectionDescriptor);

void Error_inRequestWhileConstructingWithMaxLength(int maxLength);
void Error_inRequestBeforeFinishedCheck(char endCharacter);
void Error_inRequestBeforeCommandCheck(char endCharacter);
void Error_inRequestBeforeGettingArgument(char endCharacter);
void Error_inRequestAfterGettingArgument(char isFound, int orderNumber);
void Error_inRequestBeforeGettingArguments(char endCharacter);

void Error_inResponseWhileConstructingWithMaxLength(int maxLength);
void Error_inResponseBeforeLength(char endCharacter);
void Error_inResponseBeforeAddingNumber(char endCharacter);

void Error_inServerAfterForking(int processId);

#endif

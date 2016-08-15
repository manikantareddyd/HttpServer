
//Generic Shit
void *intTostr(int a);
int scan(char *input, char *output, int start, int max);
int writeToSocket(char *messageBuffer, FILE *writeSocket);

//Connection Handlers
int checkRequest();
void handleConnection();
void acceptNewConnection();

//GET Request Handlers
void sendString();
void sendHeader(char *statusCode, char *contentType, char * contentLength, FILE *writeSocket);
void handleGetRequest();
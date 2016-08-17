
void sendString(char *message, FILE *writeSocket);
void sendHeader(char *statusCode, char *contentType, char * contentLength,char *connection);
void handle200(std::string mimeType,int fileLength,FILE *file);
void handle404();
void sendFile(FILE *file);
std::string getMimeType(string path);

void handleGetRequest(HttpRequest request)
{
	if(DEBUG) 
		printf("Handling Get Request\n");
	std::string resource =request.RequestedResource();
	if(resource == "/") resource = "/index.html";
	std::string path = rootDir+resource;
	FILE *file = fopen(path.c_str(),"r");
	std::string mimeType = getMimeType(path);
	if(file!=NULL)
	{
		handle200(mimeType,getFileLength(path),file);
	}
	else
	{
		handle404();
	}
	fclose(file);
}

void handle404()
{
	printf("Handling 404\n");
	std::string message = "<center>ERROR 404. Requested File not found.\r\n</center>";
	char numBuf[5];
	memset(numBuf,0,5);
	sprintf(numBuf,"%ld",message.length());
	sendHeader((char *)"404 Not Found",(char *)"text/html",numBuf,(char *)"keep-alive");
	memset(messageBuffer,0,4096);
	sprintf(messageBuffer,"%s",(char *)message.c_str());
	send(clientSockId,messageBuffer,message.length(),0);
}

void handle200(std::string mimeType,int fileLength,FILE *file)
{
	char numBuf[5];
	memset(numBuf,0,5);
	sprintf(numBuf,"%d",fileLength);
	sendHeader((char *)"200 OK",(char *)mimeType.c_str(),numBuf,(char *)"keep-alive");
	sendFile(file);
}

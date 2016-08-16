
void sendString(char *message, FILE *writeSocket);
void sendHeader(char *statusCode, char *contentType, char * contentLength,char *connection);
void handle200(string mimeType,int fileLength,FILE *file);
void handle404();


void handleGetRequest(HttpRequest request)
{
	string path = "."+request.RequestedResource();
	FILE *file = fopen(path.c_str(),"r");
	char ext[10];
	memset(ext,0,10);
	getExtension((char *)path.c_str(),ext,10);
	if(file!=NULL)
	{
		string mimeType = "text/html";
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
	string message = "Requested File not found. ERROR 404\r\n";
	char numBuf[5];
	memset(numBuf,0,5);
	sprintf(numBuf,"%ld",message.length());
	sendHeader((char *)"404 Not Found",(char *)"text/html",numBuf,(char *)"keep-alive");
	memset(messageBuffer,0,4096);
	sprintf(messageBuffer,"%s",(char *)message.c_str());
	send(clientSockId,messageBuffer,message.length(),0);
}

void handle200(string mimeType,int fileLength,FILE *file)
{
	char numBuf[5];
	memset(numBuf,0,5);
	sprintf(numBuf,"%d",fileLength);
	sendHeader((char *)"200 OK",(char *)mimeType.c_str(),numBuf,(char *)"keep-alive");
	while(1)
	{
		memset(messageBuffer,0,4096);
		int bytesRead = fread(messageBuffer,1,4096,file);
		if(!bytesRead)
		{
			break;
		}
		send(clientSockId,messageBuffer,4096,0);
	}
}

void sendHeader(char *statusCode, char *contentType, char *contentLength, char *connection )
{
	string header;
	header = 
		"\r\nHTTP/1.1 "+(string)statusCode+"\r\n"+
		"Content-Length:"+(string)contentLength+"\r\n"+
		"Content-Type:"+(string)contentType+"\r\n"+
		"Connection:"+(string)connection+"\r\n"+
		"\r\n";
	send(clientSockId,(char *)header.c_str(),header.length(),0);
}

void sendString(char *message, FILE *writeSocket)
{
	writeToSocket(message,writeSocket);
}

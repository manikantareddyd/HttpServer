
void sendHeader(char *statusCode, char *contentType, char *contentLength, char *connection )
{
	std::string header = 
		"\r\nHTTP/1.1 "+(std::string)statusCode+"\r\n"+
		"Content-Length:"+(std::string)contentLength+"\r\n"+
		"Content-Type:"+(std::string)contentType+"\r\n"+
		"Connection:"+(std::string)connection+"\r\n"+
		"\r\n";
	send(clientSockId,(char *)header.c_str(),header.length(),0);
}

void sendFile(FILE *file)
{
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
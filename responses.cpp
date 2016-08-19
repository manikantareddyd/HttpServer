
void sendHeader(char *statusCode, char *contentType, char *contentLength, char *connection )
{
	

	std::string header = 
		"\r\nHTTP/1.1 "+(std::string)statusCode+"\r\n"+
		"Date:"+getNowTime()+"\r\n"+
		"Content-Length:"+(std::string)contentLength+"\r\n";
	if((std::string)contentType == "unknown")
		header = header + "Media-Type: Application/octet-stream\r\n";
	else
		header = header + "Content-Type:"+(std::string)contentType+"\r\n";
	header = header +
		"Connection:"+(std::string)connection+"\r\n"+
		"\r\n";
	send(clientSockId,(char *)header.c_str(),header.length(),0);
}

void sendFile(FILE *file)
{
	while(1)
	{
		memset(messageBuffer,0,BUFFERSIZE);
		int bytesRead = fread(messageBuffer,1,BUFFERSIZE,file);
		if(!bytesRead)
		{
			break;
		}
		send(clientSockId,messageBuffer,BUFFERSIZE,0);
	}
}
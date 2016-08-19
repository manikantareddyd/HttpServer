void handle501(std::string connection)
{
    printf("Handling 501\n");
	std::string message = "<center>ERROR 501. Requested Method is not Implemented.\r\n</center>";
	char numBuf[5];
	memset(numBuf,0,5);
	sprintf(numBuf,"%ld",message.length());
	sendHeader((char *)"501 Not Implemented",(char *)"text/html",numBuf,(char *)connection.c_str());
	memset(messageBuffer,0,BUFFERSIZE);
	sprintf(messageBuffer,"%s",(char *)message.c_str());
	send(clientSockId,messageBuffer,message.length(),0);
}

void handle404(std::string connection)
{
	printf("Handling 404\n");
	std::string message = "<center>ERROR 404. Requested File not found.\r\n</center>";
	char numBuf[5];
	memset(numBuf,0,5);
	sprintf(numBuf,"%ld",message.length());
	sendHeader((char *)"404 Not Found",(char *)"text/html",numBuf,(char *)connection.c_str());
	memset(messageBuffer,0,BUFFERSIZE);
	sprintf(messageBuffer,"%s",(char *)message.c_str());
	send(clientSockId,messageBuffer,message.length(),0);
}

void handle200(std::string mimeType,int fileLength,FILE *file,std::string connection)
{
	char numBuf[5];
	memset(numBuf,0,5);
	sprintf(numBuf,"%d",fileLength);
	sendHeader((char *)"200 OK",(char *)mimeType.c_str(),numBuf,(char *)connection.c_str());
	sendFile(file);
}

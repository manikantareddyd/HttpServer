void handle501();
void handlePostRequest(HttpRequest request)
{
    handle501();
}
void handle501()
{
    printf("Handling 501\n");
	std::string message = "<center>Requested Method is not Implemented. ERROR 501\r\n</center>";
	char numBuf[5];
	memset(numBuf,0,5);
	sprintf(numBuf,"%ld",message.length());
	sendHeader((char *)"501 Not Implemented",(char *)"text/html",numBuf,(char *)"keep-alive");
	memset(messageBuffer,0,4096);
	sprintf(messageBuffer,"%s",(char *)message.c_str());
	send(clientSockId,messageBuffer,message.length(),0);
}
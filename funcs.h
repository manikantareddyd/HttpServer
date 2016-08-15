#include <stdio.h>
// #include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void sendString(char *message, FILE *writeSocket)
{
	writeToSocket(message,writeSocket);
}

void sendHeader(char *statusCode, char *contentType, char * contentLength, FILE *writeSocket)
{
	int headerLength = 
		strlen("\r\nHTTP/1.1 ")+
		strlen(statusCode)+
		strlen("\r\nContent-Length:")+strlen(contentLength)+
		strlen("\r\nContent-Type:")+strlen(contentType)+
		strlen("\r\n");
	
	char header[headerLength+atoi(contentLength)];
	memset(header,0,headerLength+20);
	strcpy(header,"\r\nHTTP/1.1 ");
	strcat(header,statusCode);
	strcat(header,"\r\nContent-Length:");
	strcat(header,contentLength);
	strcat(header,"\r\nContent-Type:");
	strcat(header,contentType);
	strcat(header,"\r\n\r\n");
	strcat(header,"<html><head></head><body>poop</body></html>\r\n");
	printf("%s\r\n",header);
	sendString(header,writeSocket);
}

void handleGetRequest()
{
    char file[200];
    memset(file,0,200);
    scan(messageBuffer,file,5,200);
    printf("%s\n",file);
	FILE *writeSocket = fdopen(dup(clientSockId), "w"); 
	//sendString(messageBuffer,clientSocId);
	char numBuf[5];
	memset(numBuf,0,5);
	sprintf(numBuf,"%d",45);
	sendHeader("200 OK", "text/plain",numBuf, writeSocket);
	fclose(writeSocket);
}


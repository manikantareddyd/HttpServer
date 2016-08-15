#include <stdio.h>
// #include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int scan(char *input, char *output, int start, int max)
{
    /*
        This is a motherfucking piece of code. 
        All it does is extract the request type from the input
        LOL
    */
	if ( start >= strlen(input) )
		return -1;

	int appending_char_count = 0;
	int i = start;
	int count = 0;

	for ( ; i < strlen(input); i ++ )
	{
		if ( *(input + i) != '\t' && *(input + i) != ' ' && *(input + i) != '\n' && *(input + i) != '\r')
		{
			if (count < (max-1))
			{
				*(output + appending_char_count) = *(input + i ) ;
				appending_char_count += 1;

				count++;
			}		
		}	
		else
			break;
	}
	*(output + appending_char_count) = '\0';	

	i += 1;

	for (; i < strlen(input); i ++ )
	{
		if ( *(input + i ) != '\t' && *(input + i) != ' ' && *(input + i) != '\n' && *(input + i) != '\r')
			break;
	}

	return i;
}



void *intTostr(int a)
{
	memset(intstr,0,4);
	int i;
	for(i=0;i<4;i++)
	{
		intstr[3-i] = '0' + a%10;
		a = a/10;
	}
	intstr[4] = 0;
}
//Not for recreational purposes
int writeToSocket(char *messageBuffer, FILE *writeSocket)
{
    
	int bytesToWrite = 4096;
	int bytesWritten = 0;
	int bytesOverHead = 0;
	while(1)
	{
		bytesWritten = fwrite( 
			messageBuffer + bytesOverHead,
			1,
			bytesToWrite,
			writeSocket
		);
		fflush(writeSocket);
		if(bytesWritten == bytesToWrite) 
			break;
		else
		{
			bytesOverHead = bytesOverHead + bytesWritten;
			bytesToWrite = 4096 - bytesOverHead;
		}
	}
    return 1;
}


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


int checkrequest()
{
    char requestType[5];
    memset(requestType,0,5);
    if(strlen(messageBuffer) <= 0)
    {
        return 0;
    }
    scan(messageBuffer,requestType,0,5);
	printf("Request Type: %s\n",requestType);
    if(strcmp("GET",requestType)==0)
    {
        
        return 1;
    }
	else if(strcmp("POST",requestType)==0)
	{
		return 2;
	}
    else if(strcmp("HEAD",requestType)==0)
    {
        return 3;
    }
	else
	{
		return 0;
	}
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

void handleConnection()
{
	if(DEBUG)
        printf("Handling Connection Request\n\n");

	while(1)
	{
		memset(messageBuffer,0,4096);
        bytesRead = recv(
            clientSockId,
            messageBuffer,
            4096,
            0
        );
		if(bytesRead <= 0)
		{
			printf("Client has closed connection\r\n");
			break;
		}
		printf("bytesRead %d\n",bytesRead);
        if(DEBUG)
            printf("Message Read\n%d\n",bytesRead);
        
        int request = checkrequest();

        if(request == 1)
        {
            handleGetRequest();
			printf("Request has been Handled\n");
        }
		else
		{
			break;
		}
    }
	return;
}




void acceptNewConnection()
{

	serverStorageSize = sizeof(serverStorage);
	clientSockId = accept(
		serverSockId, 
		(struct sockaddr *)&serverStorage,
		&serverStorageSize
	);
	if(clientSockId < 0)
	{
		printf("I can't accept this socket\n");
		exit(0);
	}
	if(fork()==0)
	{
		close(listenStatus);
		if(DEBUG)
			printf("New Connection accepted \n");
		handleConnection();
		close(clientSockId);
		if(DEBUG)
			printf("Connection Closed\nListening for new stuff\n\n");
		exit(0);
	}
	else
	{
		close(clientSockId);
	}
	
}
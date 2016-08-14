#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
	strcat(header,"<html><head></head><body>poop</body></html>");
	printf("%s\r\n",header);
	sendString(header,writeSocket);
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

int checkrequest()
{
    char requestType[5];
    memset(requestType,0,5);
    scan(messageBuffer,requestType,0,5);
    if(strlen(messageBuffer) <= 0)
    {
        return 0;
    }
    if(strcmp("GET",requestType)==0)
    {
        printf("Request Type: %s\n",requestType);
        return 1;
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
	printf("DaUFq2\n");
	
	char numBuf[5];
	printf("DaUFq2\n");
	sprintf(numBuf,"%d",43);
	printf("DaUFq\n");
	
	sendHeader("200 OK", "text/html",numBuf, writeSocket);

	fclose(writeSocket);

}

void handleConnection(int clientSockId)
{
	FILE *readSocket = fdopen(dup(clientSockId),"r");		
	if(DEBUG)
        printf("Handling Connection Request\n");

	// while(1)
	// {
		memset(messageBuffer,0,4096);
		// bytesRead = fread(
		// 	messageBuffer,
		// 	1, 
		// 	4096, 
		// 	readSocket
		// );
        bytesRead = recv(
            clientSockId,
            messageBuffer,
            4096,
            0
        );
		if(bytesRead == 0)
		{
			return;
		}

        if(DEBUG)
            printf("Message Read\n%d\n",bytesRead);
        
        int request = checkrequest();

        if(request == 1)
        {
            handleGetRequest();
        }
    // }
		
	fclose(readSocket);
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
    if(DEBUG)
        printf("New Connection accepted \n");
	
    handleConnection(clientSockId);

	close(clientSockId);
}
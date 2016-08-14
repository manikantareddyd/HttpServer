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
int sendMessage(char *messageBuffer, FILE * writeSocket)
{
	int bytesToWrite = 4096;
	int bytesWritten = 0;
	int bytesOverHead = 0;
	while(1){
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
}

void handleConnection(int clientSockId)
{
	FILE *readSocket = fdopen(dup(clientSockId),"r");		
	

	while(1)
	{
		memset(messageBuffer,0,4096);
		bytesRead = fread(
			messageBuffer,
			1, 
			4096, 
			readSocket
		);
		if(bytesRead == 0)
		{
			break;
		}
        
        int request = checkrequest();

        if(request == 1)
        {
            handleGetRequest();
        }
    }
		
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

	handleConnection(clientSockId);

	close(clientSockId);
}
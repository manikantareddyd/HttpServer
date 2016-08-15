int checkRequest();
void handleConnection();
void acceptNewConnection();

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
        
        int request = checkRequest();

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

int checkRequest()
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
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
	int pid;
	if(fork()==0)
	{
		close(listenStatus);

		if(DEBUG)
			printf("New Connection accepted PID: %d\n",getpid());

		handleConnection();

		close(clientSockId);
		close(serverSockId);
		if(DEBUG)
			printf("Connection Closed\nChild Process will exit now\n\n");
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

		if(DEBUG)
		{
			printf("%s\n",messageBuffer);
			printf("bytesRead %d\n",bytesRead);
		}

		HttpRequest request(messageBuffer);
		
		keepAlive = request["Connection"] != "Close";

		if(request.RequestType() == "GET")
		{
			handleGetRequest(request);
			if(DEBUG) 
				printf("Request has been Handled\n");
		}
		else
		{
			handleBadRequest();
			break;
		}
		if(!keepAlive)
		{
			break;
		}
		
    }
	return;
}

void createSocket()
{
	/* 
		We will generate a socket for our usage.
		A descriptor
	*/
	serverSockId = socket(
		AF_INET, 
		SOCK_STREAM, 
		0
	);
	if(serverSockId == -1)
	{
		printf("Something went wrong with socket generation.\nPlease try again :P \n");
		exit(0);
	}
	if(DEBUG)
		printf("Socket Created\n");
}

void bindSocket()
{
	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(PORT);
	serverSockAddr.sin_addr.s_addr = INADDR_ANY;
	

	/*
		We'll bind the descriptor with the socket.
		From now on we can refer to descriptor for the coket
	*/
	status = bind(
		serverSockId, 
		(struct sockaddr *)&serverSockAddr, 
		sizeof(serverSockAddr)
	);
	if(status == -1)
	{
		fprintf(stderr,"This socket port seems occupied!\n");
		exit(0);
	}
	if(DEBUG)
		printf("Socket Binding Done\n");
}

void listenThroughSocket()
{
	/*
		We'll start listenig through this socket, 
		whether anyone wants to connect.
	*/
	listenStatus = listen(serverSockId , 3);
	if(listenStatus < 0)
	{
		fprintf(stderr,"I can't listen to this port right now. Please try again!\n");
		exit(0);
	}

	if(DEBUG)
		printf("Socket Listening\n");
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
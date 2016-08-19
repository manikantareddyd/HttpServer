void handleConnection()
{
	if(DEBUG)
        printf("Handling Connection Request\n\n");

	while(1)
	{
		memset(messageBuffer,0,BUFFERSIZE);
        bytesRead = recv(
            clientSockId,
            messageBuffer,
            BUFFERSIZE,
            0
        );

		if(bytesRead <= 0)
		{
			if(DEBUG) printf("Client has closed connection\r\n");
			break;
		}

		if(DEBUG)
		{
			printf("%s\n",messageBuffer);
			printf("bytesRead %d\n",bytesRead);
		}

		if(!(messageBuffer[bytesRead-1] == '\n' && messageBuffer[bytesRead-2]=='\r'))
		{
			handleBadRequest();
			continue;
		}

		HttpRequest request(messageBuffer);

		
		logToFile(request);
				
		
		if(getConnection(request) == "close")
			keepAlive = 0;
			
		if(DEBUG)
			cout<<"Request Type: "<<request.RequestType()<<endl;
		if(request.RequestType() == "GET")
		{
			handleGetRequest(request);
			if(DEBUG) 
				printf("GET Request has been Handled\n");
		}
		else if(request.RequestType() == "POST")
		{
			handlePostRequest(request);
			if(DEBUG)
				printf("POST Request has been Handled\n");
		}
		else if(request.RequestType() == "HEAD")
		{
			handleHeadRequest(request);
			if(DEBUG)
				printf("HEAD Request has been Handled\n");
		}
		else
		{
			handleBadRequest();
			continue;
		}
		if(!keepAlive)
		{
			if(DEBUG) cout<<"Breaking Off"<<endl;
			break;
		}
    }
	return;
}

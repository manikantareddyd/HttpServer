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
			break;
		}
		if(!keepAlive)
		{
			break;
		}
    }
	return;
}


void *intTostr(int a)
{
	/*
		This function converts int between
		0-4096 as stirngs of size 5 bytes
	*/
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
	/*
		This is a helper function to correctly write to socket buffer.
		It needs a message buffer and file pointer of the socket to which
		we will be writing.
	*/
	int bytesToWrite = 4096;
	int bytesWritten = 0;
	int bytesOverHead = 0;
	/*
		We need to loop till all writable bytes are written to socket buffer.
		If write fails in between we loop back and write the remaining bytes
	*/
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


void handleRequests(int clientSockId)
{
	/*
		Here's a pretty dumb and awesome thing we'll do.
		We'll treat the socket as a 'File'. Yes as a 'File'.
		We'll use two files. One for writng and the other for reading.
		We can generate the file pointers using fdopen. Read Man pages
	*/		
	FILE *readSocket = fdopen(dup(clientSockId),"r");		
	
	
	/*
		Empty the buffer and send a welcome message.
        Update: Http Server has no requirement of this :p'
	*/
	// memset(messageBuffer,0,4096);
	// strcpy(messageBuffer, "Server: Welcome - We just connected\n");
	// sendMessage(messageBuffer,writeSocket);
	

	while(1)
	{
		/*
			This loop is ensure the connection with the same
			client, unless the client itself closes connection.
		*/

		/*
			We read message from client( A File name)
		*/
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
        
        int request = checkrequest(messageBuffer);

        if(request == 1)
        {
            handleGetRequest();
        }

		
	fclose(readSocket);
	fclose(writeSocket);
}

void handleGetRequest()
{
    //I need to write this
}
void acceptNewConnection()
{
	/*
		We accept the connection request sent by client
		and receive a descriptor for the clients socket.
	*/
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

	handleRequests(clientSockId);

	close(clientSockId);
}
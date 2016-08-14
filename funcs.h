
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
	FILE *writeSocket = fdopen(clientSockId, "w");
	FILE *readSocket = fdopen(dup(clientSockId),"r");		
	
	
	/*
		Empty the buffer and send a welcome message.
	*/
	memset(messageBuffer,0,4096);
	strcpy(messageBuffer, "Server: Welcome - We just connected\n");
	sendMessage(messageBuffer,writeSocket);
	

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

		printf("The client needs this file: %s\n", messageBuffer);
		
		/*
			Open the file required by the client
		*/
		FILE *file;
		file = fopen(messageBuffer,"r");
		
		if(file == NULL)
		{
			/*
				If the clients request is erroneous, we
				need to tell the client its erroneous.
			*/
			memset(messageBuffer,0,4096);
			strcpy(messageBuffer,"Server: Such file doesn't exist\n");
			intTostr(333);
			snprintf(messageBuffer+4091, 5, "%s",intstr); 	
			sendMessage(messageBuffer,writeSocket);
			continue;
		}

		memset(messageBuffer,0,4096);
		strcpy(messageBuffer,"Server: I received your request\n\tHere are the File contents:");
		intTostr(24);
		snprintf(messageBuffer+4091, 5, "%s",intstr);
		sendMessage(messageBuffer,writeSocket);
		
		while(1)
		{
			/*
				This is a control loop for file reading.
				We read from a large file block by block into
				buffer and then transmit it.

			*/
			memset(messageBuffer,0,4096);
			bytesRead = fread(messageBuffer,1,4091,file);
			if(!bytesRead)
			{
				/*
					If EOF of file is reached, fread stops reading.
					So we send our custom EOF in the message buffer
					and then start listening for new message by breaking
					of this loop.
				*/
				memset(messageBuffer,0,4096);
				strcpy(messageBuffer,"<---EOF--->");
				intTostr(11);
				snprintf(messageBuffer+4091, 5, "%s",intstr);
				sendMessage(messageBuffer,writeSocket);
				break;
			}
			intTostr(bytesRead);
			/*
				We did something really cool here.
				We send the client how many bytes we read from file 
				as a integer string in the last 5 bytes.
				So the client needs to just read those many bytes, 
				although we send 4096 bytes through fwrite.
			*/
			snprintf(messageBuffer+4091, 5, "%s",intstr);
			sendMessage(messageBuffer,writeSocket);
		}
	}
	fclose(readSocket);
	fclose(writeSocket);
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
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void writeToSocket(char *messageBuffer, FILE * writeSocket);

int main( int argc, char *argv[] )
{
	int bytesReceived;
	int clientSockId;
	char messageBuffer[4096];
	int i;
	struct sockaddr_in serverSockAddr;
	
	/* 
		We will generate a socket for our usage.
		A descriptor
	*/
	clientSockId = socket(
		AF_INET, 
		SOCK_STREAM, 
		0
	);
	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(atoi(argv[2]));
	serverSockAddr.sin_addr.s_addr = inet_addr(argv[1]);
	int serverSockAddrSize = (sizeof(serverSockAddr));
	
	/* 
		We will now connect the socket we created with socket from server
		and obtain a descriptor for the same
	*/
	connect(
		clientSockId, 
		(struct sockaddr *)&serverSockAddr, 
		serverSockAddrSize
	);
	
	/*
		Here's a pretty dumb and awesome thing we'll do.
		We'll treat the socket as a 'File'. Yes as a 'File'.
		We'll use two files. One for writng and the other for reading.
		We can generate the file pointers using fdopen. Read Man pages
	*/
	FILE *writeSocket = fdopen(clientSockId, "w");
	FILE *readSocket = fdopen(dup(clientSockId),"r");
	
	/*
		We try to receive something from the server.
		Before that we set the buffer to null
	*/
	// memset(messageBuffer,0,4096);
	// bytesReceived = fread(
	// 	messageBuffer,
	// 	1,
	// 	4096,
	// 	readSocket
	// );
	
	// /*
	// 	If you don't receive anything, then the server is angry with you.
	// 	Go away
	// */
	// if(bytesReceived == 0)
	// {
	// 	printf("Server Busy\n");
	// 	/*
	// 		Lets exit. 
	// 		Stop bothering the server.
	// 	*/
	// 	return 0;
	// } 	
	
	/*
		Print the greeting message.
	*/
	//printf("%s\n",messageBuffer );
	
	
	while(1)
	{
		/*
			This loop is where we'll essentially talk to the server
		*/
		memset(messageBuffer,0,4096);
		scanf("%s",messageBuffer);
		
		/*
			This is a Safe word to tell the client to stop.
			Safe Words are must aren't they ;)
		*/
		if(!strcmp(messageBuffer,"-exit")) 
			break;
		
		/*
			We'll send our request to the server.
			Refer to the function below to know what it does.
		*/
		writeToSocket(messageBuffer,writeSocket);
		
		/*
			You know what happens here
		*/
		memset(messageBuffer,0,4096);
		bytesReceived = fread(
			messageBuffer,
			1,
			4096,
			readSocket
		);
		if(bytesReceived == 0) 
		{
			printf("Something's wrong with the server. Try again Later :( \n");
			break;
		}
		printf("%s\n", messageBuffer);
		/*
			I'll explain this in a bit
		*/
		if(atoi(messageBuffer+4091)==333) continue;
		//FILE *fp = fopen("haha","w");
		printf("--------------------------------\n\n");
		while(1)
		{
			memset(messageBuffer,0,4096);
			fread(
				messageBuffer,
				1,
				4096,
				readSocket
			);
			/*
				We did something really cool at the server.
				They send us how many bytes they sent to us 
				as a integer string in the last 5 bytes.
				So we need to just those many bytes, although we 
				read 4096 bytes through fread.
			*/
			bytesReceived = atoi(messageBuffer+4091);
			
			if(!strcmp(messageBuffer,"<---EOF--->"))	
			{
				break;
			}

			//fwrite(messageBuffer,1,bytesReceived,fp);
			fwrite(messageBuffer,1,bytesReceived,stdout);
			memset(messageBuffer,0,4096);
		}
		printf("\n--------------------------------\n");
		//fclose(fp);
	}
	fclose(readSocket);
	fclose(writeSocket);
	return 0;
}

//Not for recreational purposes
void writeToSocket(char *messageBuffer, FILE * writeSocket)
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
}
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void writeToSocket(char *messageBuffer, FILE * writeSocket)
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
}
int main( int argc, char *argv[] )
{
	int bytesReceived;
	int clientSockId;
	char messageBuffer[4096];
	int i;
	struct sockaddr_in serverSockAddr;
	clientSockId = socket(
		AF_INET, 
		SOCK_STREAM, 
		0
	);
	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(atoi(argv[1]));
	serverSockAddr.sin_addr.s_addr = inet_addr(argv[2]);
	int serverSockAddrSize = (sizeof(serverSockAddr));
	connect(
		clientSockId, 
		(struct sockaddr *)&serverSockAddr, 
		serverSockAddrSize
	);
	memset(messageBuffer,0,4096);
	FILE *writeSocket = fdopen(clientSockId, "w");
	FILE *readSocket = fdopen(dup(clientSockId),"r");
	bytesReceived = fread(
		messageBuffer,
		1,
		4096,
		readSocket
	);
	if(bytesReceived == 0)
	{
		printf("Server Busy\n");
		return 0;
	} 	
	printf("%s\n",messageBuffer );
	while(1)
	{
		memset(messageBuffer,0,4096);
		scanf("%s",messageBuffer);
		if(!strcmp(messageBuffer,"-exit")) break;
		writeToSocket(messageBuffer,writeSocket);
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
		if(atoi(messageBuffer+4091)==333) continue;
		FILE *fp = fopen("haha","w");
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
			bytesReceived = atoi(messageBuffer+4091);
			if(!strcmp(messageBuffer,"<---EOF--->"))	
			{
				break;
			}
			fwrite(messageBuffer,1,bytesReceived,fp);
			fwrite(messageBuffer,1,bytesReceived,stdout);
			memset(messageBuffer,0,4096);
		}
		printf("\n--------------------------------\n");
		fclose(fp);
	}
	fclose(readSocket);
	fclose(writeSocket);
	return 0;
}
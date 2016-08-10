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
int main( )
{
	int bytesReceived;
	int clientSockId;
	char messageBuffer[4096];
	int i;
	struct sockaddr_in serverSockAddr;
	clientSockId = socket
		(
			AF_INET, 
			SOCK_STREAM, 
			0
		);
	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(3234);
	serverSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int serverSockAddrSize = (sizeof(serverSockAddr));
	connect(
		clientSockId, 
		(struct sockaddr *)&serverSockAddr, 
		serverSockAddrSize
	);
	memset(messageBuffer,0,4096);
	FILE *writeSocket = fdopen(clientSockId, "w");
	FILE *readSocket = fdopen(dup(clientSockId),"r");
	fread(
		messageBuffer,
		1,
		4096,
		readSocket
	);	
	printf("%s\n",messageBuffer );
	while(1)
	{
		memset(messageBuffer,0,4096);
		scanf("%s",messageBuffer);
		if(messageBuffer[0]=='-') break;
		writeToSocket(messageBuffer,writeSocket);
		memset(messageBuffer,0,4096);
		bytesReceived = fread(
			messageBuffer,
			1,
			4096,
			readSocket
		);
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
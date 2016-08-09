#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main( )
{
	int clientSockId;
	char messageBuffer[4096];
	int i;
	struct sockaddr_in serverSockAddr;

	clientSockId = socket(AF_INET, SOCK_STREAM, 0);

	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(3232);
	serverSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int serverSockAddrSize = (sizeof(serverSockAddr));
	connect(clientSockId, (struct sockaddr *)&serverSockAddr, serverSockAddrSize);
	for(i=0;i<4096;i++) messageBuffer[i] = 0;
	FILE *writeSocket = fdopen(clientSockId, "w");
	FILE *readSocket = fdopen(dup(clientSockId),"r");
	fread(messageBuffer,1,4096,readSocket);	
	printf("%s\n",messageBuffer );
	while(1)
	{
		for(i=0;i<4096;i++) messageBuffer[i] = 0;
		scanf("%s",messageBuffer);
		if(messageBuffer[0]=='-') break;
		fwrite(messageBuffer,1,4096,writeSocket);
		fflush(writeSocket);
		for(i=0;i<4096;i++) messageBuffer[i] = 0;
		fread(messageBuffer,1,4096,readSocket);
		printf("%s\n",messageBuffer );
	}
	fclose(readSocket);
	fclose(writeSocket);
	return 0;
}
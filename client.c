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
	for(i=0;i<4096;i++) messageBuffer[i] = ' ';
	read(clientSockId , messageBuffer , 4096 , 0);
	printf("%s\n",messageBuffer );
	while(1)
	{
		for(i=0;i<4096;i++) messageBuffer[i] = '\0';
		scanf("%s",messageBuffer);
		send(clientSockId, messageBuffer, 4096,0 );
		for(i=0;i<4096;i++) messageBuffer[i] = '\0';
		read(clientSockId, messageBuffer, 4096, 0);
		printf("%s\n",messageBuffer );
	}
	return 0;
}
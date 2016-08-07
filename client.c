#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main( )
{
	int clientSockId;
	char Message[4096];

	struct sockaddr_in serverSockAddr;

	clientSockId = socket(AF_INET, SOCK_STREAM, 0);

	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(3232);
	serverSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int serverSockAddrSize = (sizeof(serverSockAddr));
	connect(clientSockId, (struct sockaddr *)&serverSockAddr, serverSockAddrSize);
	recv(clientSockId , Message , 4096 , 0);
	printf("%s\n",Message );
	return 0;
}
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
	int serverSockId, clientSockId;
	struct sockaddr_in serverSockAddr,clientSocAddr;
	int status;
	char clientMessage[4096];

	serverSockId = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSockId == -1){
		printf("Something went wrong with socket generation.\nPlease try again :P \n");
		return 0;
	}

	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(3232);
	serverSockAddr.sin_addr.s_addr = INADDR_ANY;

	status = bind(serverSockId, (struct sockaddr *)&serverSockAddr, sizeof(serverSockAddr));
	printf("%d\n", status);

	listen(serverSockId , 3);

	int c = (sizeof(clientSocAddr));
	clientSockId = accept(serverSockId, (struct sockaddr *)&clientSocAddr, &c);	
	clientMessage[0] = 'P';
	clientMessage[1] = '\n';
	write(clientSockId , clientMessage , 4096);
	recv(clientSockId , clientMessage , 4096, 0);
	printf("From client%s\n", clientMessage);
	return 0;
}
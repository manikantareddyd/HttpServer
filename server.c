#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
	int serverSockId, clientSockId;
	struct sockaddr_in serverSockAddr,clientSocAddr;
	int status,serverStorageSize;
	char messageBuffer[4096];
	struct sockaddr_storage serverStorage;


	serverSockId = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSockId == -1){
		printf("Something went wrong with socket generation.\nPlease try again :P \n");
		return 0;
	}

	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(3232);
	serverSockAddr.sin_addr.s_addr = INADDR_ANY;

	status = bind(serverSockId, (struct sockaddr *)&serverSockAddr, sizeof(serverSockAddr));
	listen(serverSockId , 3);
	serverStorageSize = sizeof(serverStorage);
	clientSockId = accept(serverSockId, (struct sockaddr *)&serverStorage,&serverStorageSize);
	strcpy(messageBuffer, "Poop");
	send(clientSockId, messageBuffer, strlen(messageBuffer), 0 );
	return 0;
}
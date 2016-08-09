#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
	int serverSockId, clientSockId;
	struct sockaddr_in serverSockAddr,clientSocAddr;
	int status,serverStorageSize,i;
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
	if(status == -1){
		printf("This socket port seems occupied!\n");
	}


	listen(serverSockId , 3);
	serverStorageSize = sizeof(serverStorage);
	
	while(1)
	{
		clientSockId = accept(serverSockId, (struct sockaddr *)&serverStorage,&serverStorageSize);
		for(i=0;i<4096;i++) messageBuffer[i] = '\0';
		strcpy(messageBuffer, "Welcome - We just connected");
		send(clientSockId, messageBuffer, 4096, 0 );
		for(i=0;i<4096;i++) messageBuffer[i] = ' ';
		while(read(clientSockId, messageBuffer, 4096, 0) > 0)
		{
			printf("%s\n",messageBuffer );
			for(i=0;i<4096;i++) messageBuffer[i] = '\0';
			strcpy(messageBuffer, "I received it");
			send(clientSockId, messageBuffer, 4096,0);
		}
		
	}
	return 0;
}
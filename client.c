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
	serverSockAddr.sin_port = htons(3233);
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
		memset(messageBuffer,0,4096);
		scanf("%s",messageBuffer);
		printf("I requested: %s\n",messageBuffer);

		if(messageBuffer[0]=='-') break;
		fwrite(messageBuffer,1,4096,writeSocket);
		fflush(writeSocket);
		
		memset(messageBuffer,0,4096);
		fread(messageBuffer,1,4096,readSocket);
		printf("%s\n",messageBuffer );
		
		FILE *fp = fopen("haha","w");
		while(1){
			memset(messageBuffer,0,4096);
			fread(messageBuffer,1,4096,readSocket);
			if(messageBuffer[0]=='E' && messageBuffer[1]=='O' && messageBuffer[2]=='F')	
			{
				break;
			}
			fprintf(fp,"%s", messageBuffer);
			printf("%s", messageBuffer);
			memset(messageBuffer,0,4096);
		}
		printf("\n");
		fprintf(fp,"\n");
		fclose(fp);
	
	}
	fclose(readSocket);
	fclose(writeSocket);
	return 0;
}
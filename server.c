#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

char intstr[5];
void *intTostr(int a)
{
	memset(intstr,0,4);
	int i;
	for(i=0;i<4;i++)
	{
		intstr[3-i] = '0' + a%10;
		a = a/10;
	}
	intstr[4] = 0;
	printf("%s\n", intstr);
}

int main()
{
	int serverSockId, clientSockId;
	struct sockaddr_in serverSockAddr,clientSocAddr;
	int status,serverStorageSize,i;
	char messageBuffer[4096];
	int bytesRead;

	struct sockaddr_storage serverStorage;


	serverSockId = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSockId == -1){
		printf("Something went wrong with socket generation.\nPlease try again :P \n");
		return 0;
	}

	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(3234);
	serverSockAddr.sin_addr.s_addr = INADDR_ANY;

	status = bind(serverSockId, (struct sockaddr *)&serverSockAddr, sizeof(serverSockAddr));
	if(status == -1){
		printf("This socket port seems occupied!\n");
	}


	int listenStatus = listen(serverSockId , 3);
	if(listenStatus < 0){
		printf("I can't listen to this port right now. Please try again!\n");
		return 0;
	}

	serverStorageSize = sizeof(serverStorage);
	
	while(1)
	{
		clientSockId = accept(
			serverSockId, 
			(struct sockaddr *)&serverStorage,
			&serverStorageSize
			);

		if(clientSockId < 0)
		{
			printf("I can't accept this socket\n");
			return 0;
		}

		FILE *writeSocket = fdopen(clientSockId, "w");
		FILE *readSocket = fdopen(dup(clientSockId),"r");
		
		memset(messageBuffer,0,4096);
		strcpy(messageBuffer, "Welcome - We just connected\n");
		fwrite( messageBuffer,1,4096,writeSocket);
		// intTostr(bytesRead);
		// snprintf(messageBuffer+4091, 4, intstr)
		fflush(writeSocket);
		while(1)
		{
			memset(messageBuffer,0,4096);
			if(!fread(messageBuffer,1, 4096, readSocket)){
				break;
			}
			printf("The client needs this file: %s\n", messageBuffer);
			FILE *file;
			file = fopen(messageBuffer,"r");
			if(file == NULL)
			{
				memset(messageBuffer,0,4096);
				strcpy(messageBuffer,"Such file doesn't exist\n");
				intTostr(24);
				snprintf(messageBuffer+4091, 5, intstr); 	
				fwrite(messageBuffer,1,4096,writeSocket);
				fflush(writeSocket);
				
				strcpy(messageBuffer,"MMM");
				intTostr(3);
				snprintf(messageBuffer+4091, 5, intstr); 	
				fwrite(messageBuffer,1,4096,writeSocket);
				fflush(writeSocket);
				continue;
			}

			memset(messageBuffer,0,4096);
			strcpy(messageBuffer,"I received your request\n");
			fwrite(messageBuffer,1,4091,writeSocket);
			fflush(writeSocket);
			
			while(1)
			{
				memset(messageBuffer,0,4096);
				bytesRead = fread(messageBuffer,1,4091,file);
				printf("bytes read 1: %d\n", bytesRead);
				if(!bytesRead)
				{
					memset(messageBuffer,0,4096);
					strcpy(messageBuffer,"MMM");
					intTostr(bytesRead);
					snprintf(messageBuffer+4091, 5, intstr);
					fwrite(messageBuffer,1,4096,writeSocket);
					fflush(writeSocket);
					//printf("Broke\n");
					break;
				}
				intTostr(bytesRead);
				snprintf(messageBuffer+4091, 5, intstr);
				fwrite(messageBuffer,1,4096,writeSocket);
				fflush(writeSocket);
			}
		}
		fclose(readSocket);
		fclose(writeSocket);
	}
	return 0;
}


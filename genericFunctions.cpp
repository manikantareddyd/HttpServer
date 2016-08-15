//Not for recreational purposes
void *intTostr(int a);
int scan(char *input, char *output, int start, int max);
int writeToSocket(char *messageBuffer, FILE *writeSocket);

void sigintHandler(int sig_num)
{
	//Helps to keep ports from being blocked when we close the server :P
	close(listenStatus);
	close(clientSockId);
	close(serverSockId);
	exit(0);
}

int writeToSocket(char *messageBuffer, FILE *writeSocket)
{
    
	int bytesToWrite = 4096;
	int bytesWritten = 0;
	int bytesOverHead = 0;
	while(1)
	{
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
    return 1;
}

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
}

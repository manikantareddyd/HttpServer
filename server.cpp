
#include "server.h"

int main(int argc, char *argv[])
{
	signal(SIGINT, sigintHandler);
	if(argv[1]!=NULL)
		PORT = atoi(argv[1]);
	if(argv[2]!=NULL) 
		rootDir = argv[2];
	createSocket();
	bindSocket();
	listenThroughSocket();
	
	while(1)
	{
		acceptNewConnection();
	}
	return 0;
}

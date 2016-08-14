
#include "server.h"


int main(int argc, char *argv[])
{
	PORT = atoi(argv[1]);
	createSocket();
	bindSocket();
	listenThroughSocket();
	
	while(1)
	{
		acceptNewConnection();
	}
	return 0;
}

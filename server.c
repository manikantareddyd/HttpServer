
#include "server.h"


int main(int argc, char *argv[])
{
	PORT = atoi(argv[1]);
	createSocket();
	bindSocket();
	listenThroughSocket();
	
	/*
		This is a persistence loop to facilitate
		for multiple connections - one by one.
	*/
	while(1)
	{
		acceptNewConnection();
	}
	return 0;
}

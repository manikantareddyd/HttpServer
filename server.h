//Libraries
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ctime>

//My files
#include "globals.cpp"
#include "utils/clews/http/HttpRequest.cpp"
#include "genericFunctions.cpp"
#include "sendResponses.cpp"
#include "responseHandlers.cpp"
#include "getRequestHandlers.cpp"
#include "headRequestHandlers.cpp"
#include "postRequestHandlers.cpp"
#include "badRequestHandlers.cpp"
#include "connectionHandler.cpp"
#include "SocketFunctions.cpp"

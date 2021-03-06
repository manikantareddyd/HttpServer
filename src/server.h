//Libraries
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <mutex>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ctime>

#include <sys/types.h>
#include <sys/stat.h>

//My files
#include "globalVariables.cpp"
#include "../utils/clews/http/HttpRequest.cpp"
#include "genericFunctions.cpp"
#include "responses.cpp"
#include "responseHandlers.cpp"
#include "getRequestHandlers.cpp"
#include "headRequestHandlers.cpp"
#include "postRequestHandlers.cpp"
#include "badRequestHandlers.cpp"
#include "connectionHandler.cpp"
#include "socketFunctions.cpp"

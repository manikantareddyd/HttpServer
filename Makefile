all: servermake

servermake: server.cpp server.h badRequestHandlers.cpp  globalVariables.cpp      responses.cpp connectionHandler.cpp   headRequestHandlers.cpp  genericFunctions.cpp    postRequestHandlers.cpp  socketFunctions.cpp getRequestHandlers.cpp  responseHandlers.cpp
	g++ -pthread -static -std=c++11 server.cpp -o http-server

clean:
	rm http-server

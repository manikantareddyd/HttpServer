all: servermake

servermake: src/server.cpp
		g++ -pthread -static -std=c++11 src/server.cpp -o http-server

clean:
	rm http-server

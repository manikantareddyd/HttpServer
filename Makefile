all: servermake

servermake: server.cpp
	g++ -pthread -static -std=c++11 server.cpp -o server

clean:
	rm server

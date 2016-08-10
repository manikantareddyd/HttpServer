all: servermake clientmake

servermake: server.c
	gcc server.c -o server

clientmake: client.c
	gcc client.c -o client
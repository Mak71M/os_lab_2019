CC=gcc
all: server client

server:
	$(CC) -pthread server.c -o server.o	
client:
	$(CC) -pthread client.c -o client.o
clean:
	rm server.o client.o
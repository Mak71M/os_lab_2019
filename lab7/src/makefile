CC=gcc
all: tcpserver tcpclient udpserver updclient

tcpserver:
	$(CC) tcpserver.c -o tcpserver.o	
tcpclient:
	$(CC) tcpclient.c -o tcpclient.o
udpserver:
	$(CC) udpserver.c -o udpserver.o
updclient:
	$(CC) udpclient.c -o udpclient.o
clean:
	rm tcpserver.o tcpclient.o udpserver.o udpclient.o
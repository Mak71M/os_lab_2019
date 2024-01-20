CC=gcc
all: mutex parallel_factorial deadlock
mutex: mutex.c
	$(CC) -pthread mutex.c -o mutex.o
parallel_factorial: parallel_factorial.c
	$(CC) -pthread parallel_factorial.c -o parallel_factorial.o
deadlock: deadlock.c
	$(CC) -pthread deadlock.c -o deadlock.o
clean:
	rm mutex.o parallel_factorial.o deadlock.o
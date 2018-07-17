all: Server

Server: server.o libsocksLib.a
	gcc -lm -o Server server.o -L. -lsocksLib

server.o: server.c
	gcc -O -c server.c

client.o: client.c
	gcc -O -c client.c

socksLib.o: socksLib.c socksLib.h
	gcc -O -c socksLib.c

libsocksLib.a: socksLib.o
	ar rcs libsocksLib.a socksLib.o

.PHONY: clean

clean:
	rm -rf Server Client *.o *.a *.gch

.PHONY: client

client: client.o libsocksLib.a
	gcc -lm -o Client client.o -L. -lsocksLib

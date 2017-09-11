CC=gcc
FLAGS= -I ../include -g
EXECPATH= ../
OBJPATH= ../src/

default: server clean

server: server.o hashing.o
	$(CC) -o $(EXECPATH)server server.o hashing.o  -g

server.o: server.c
	$(CC) $(FLAGS) -c server.c
 
hashing.o: $(OBJPATH)hashing.c
	$(CC) $(FLAGS) -c $(OBJPATH)hashing.c

clean:
	rm -rf server.o hashing.o





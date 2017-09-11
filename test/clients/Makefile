CC=gcc
FLAGS= -I ../../include -g
EXECPATH= ../../

default: tcp_client udp_client client_lookup client_delete clean

tcp_client: tcp_client.o 
	$(CC) -o $(EXECPATH)tcp_client tcp_client.o -g

udp_client: udp_client.o
	$(CC) -o $(EXECPATH)udp_client udp_client.o -g
client_lookup:client_lookup.o
	 $(CC) -o $(EXECPATH)client_lookup client_lookup.o -g

client_delete:client_delete.o
	$(CC) -o $(EXECPATH)client_delete client_delete.o -g
tcp_client.o: tcp_client.c
	$(CC) -c $(FLAGS) tcp_client.c 

udp_client.o: udp_client.c
	$(CC) -c $(FLAGS) udp_client.c
client_lookup.o:client_lookup.c
	$(CC) -c $(FLAGS) client_lookup.c
client_delete.o:client_delete.c
	$(CC) -c $(FLAGS) client_delete.c

clean:
	rm -rf *.o

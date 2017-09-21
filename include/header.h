#ifndef HASH_COLI
#define HASH_COLI

#include <stdio.h> 
#include <string.h>   
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   
#include <arpa/inet.h>  
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> 
#include <time.h>  
#include<netinet/if_ether.h>
#include<netinet/ip.h>
#include<netinet/tcp.h>
#include<math.h>




#define MAX 65535
struct packet{     /*this packet contains protocol number,source port,destination port,time stamp,source address and destination address both in int and string form*/
int protocol;
char src_addr[50];
char dest_addr[50];
int src_port,dest_port;
unsigned long int src,dest;
char time[50];
};


struct colisched{   /*structure for hash table*/
char time[50];
int src,dest,src_port,dest_port,protocol;
struct colisched *ptr;
};




void hash_lookup(void *);  /*from here below three are the main three functions used for inserting,searching and deleting a number*/
void hash_insert(void *);
void hash_del(void *);



int coli_index(struct packet *);      /*below four functions are used to do the internal operations in the hash table*/
/*the above function returns the index value to store in the hash table for incoming packet*/
struct colisched *update_array_size(struct colisched *);/*when ever cellar becomes full it increases the size of cellar by asking user ammount of size to increase*/
int gap_coli(struct packet *p,int index);
void coli_insert(struct packet *,int); /*one of the internal function used for inserting the incoming packet into hash table.*/


#endif

/*struct packet *pckt;*/





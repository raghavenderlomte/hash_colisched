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
struct packet{     //different fields which are used in a single packet
int protocol;
char src_addr[50];
char dest_addr[50];
int src_port,dest_port;
unsigned long int src,dest;
char time[50];
};


void hash_lookup(void *);  //from here below three are the main three functions used for inserting,searching and deleting a number
void hash_insert(void *);
void hash_del(void *);



int coli_index(struct packet *);      //below four functions are used to do the internal operations in the hash table
struct colisched *update_array_size(struct colisched *);
int gap_coli(struct packet *p,int index);
void coli_insert(struct packet *,int);



struct colisched{   //structure for hash table
char time[50];
int src,dest,src_port,dest_port,protocol;
struct colisched *ptr;
};


//struct packet *pckt;





#include "header.h"
#define ADDRESS "127.0.0.1"
#define PORT 8080

    
int main(char *argv[],int argc)
{
struct packet *packt;
packt=(struct packet *)malloc(sizeof(struct packet));  /*allocating memory for packet*/
memset(packt,'\0',sizeof(struct packet));

int clnt_fd,rtrn,addrlen,a;
char b[100];
struct sockaddr_in client_addr,address;
clnt_fd=socket(AF_INET,SOCK_STREAM,0);
if(clnt_fd == -1)
{
	perror("socket error\n");
	return -1;
}
    	client_addr.sin_family = AF_INET;  				
	client_addr.sin_addr.s_addr = inet_addr(ADDRESS);  
	client_addr.sin_port = htons(PORT); 
	addrlen=sizeof(client_addr);
	printf("enter the source addr\n");	/*filling the data in packet */
	scanf(" %[^\n]s",b);
	address.sin_addr.s_addr=inet_addr(b);

	strcpy(packt->src_addr,inet_ntoa(address.sin_addr));
	printf("enter the destination addr\n");
	scanf(" %[^\n]s",b);
	address.sin_addr.s_addr=inet_addr(b);
	printf("%s\n",b);
	strcpy(packt->dest_addr,inet_ntoa(address.sin_addr));
	printf("enter the source port num\n");
	scanf(" %d",&a);
	packt->src_port=a;
	printf("enter the destination port num\n");
	scanf("%d",&a);
	packt->dest_port=a;
	packt->src=(unsigned long int)ntohl(address.sin_addr.s_addr);
	packt->dest=(unsigned long int)ntohl(address.sin_addr.s_addr);
	printf("enter the protocol num\n");
	printf("6->tcp\n");
	printf("17->udp\n");
	scanf("%d",&a);
	packt->protocol=a;
	strcpy(packt->time,"delete");
	printf("%s\n",packt->time);
	printf("%s\n",packt->src_addr);
	printf("%s\n",packt->dest_addr);
	printf("%d\n",packt->src_port);
	printf("%d\n",packt->dest_port);
	printf("%d\n",packt->protocol);
	rtrn=connect(clnt_fd,(struct sockaddr *)&client_addr,(socklen_t)addrlen); /*connecting to server*/
	if(rtrn == -1)
	{
		perror("connect error\n");
		return -1;
	}
	write(clnt_fd,(char *)packt,sizeof(struct packet)); /*sending the packet to server*/
	



}

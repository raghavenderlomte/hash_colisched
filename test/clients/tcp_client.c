#include "header.h"    
#define ADDRESS "127.0.0.1"
#define PORT 8080
 

int main()
{
int clnt_fd,rtrn,addrlen;
char rcvbuff[100];
char buffer[50];
struct sockaddr_in client_addr;
clnt_fd=socket(AF_INET,SOCK_STREAM,0);
if(clnt_fd == -1)
{
	perror("socket error\n");
	return -1;
}
	memset(rcvbuff,'\0',sizeof(rcvbuff));
    	client_addr.sin_family = AF_INET;  
	client_addr.sin_addr.s_addr = inet_addr(ADDRESS);  
	client_addr.sin_port = htons(PORT); 
	addrlen=sizeof(client_addr);
	rtrn=connect(clnt_fd,(struct sockaddr *)&client_addr,(socklen_t)addrlen);
	if(rtrn == -1)
	{
		perror("connect error\n");
		return -1;
	}
//	read(clnt_fd,rcvbuff,sizeof(rcvbuff));
//	printf("data from server=%s\n",rcvbuff);
	printf("enter the data to send to server\n");
	scanf("%[^\n]s",buffer);
	write(clnt_fd,buffer,sizeof(buffer));
	
	close(clnt_fd);
}

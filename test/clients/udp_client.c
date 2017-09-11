#include "header.h"
#define ADDRESS "127.0.0.1"
#define PORT 8080
 

int main()
{
struct sockaddr_in si_other;
char message[]="hello bhai \n";
int client_fd,rtrn, i, slen=sizeof(si_other);
client_fd=socket(AF_INET, SOCK_DGRAM,0);
if(-1==client_fd)
{
	perror("socket error\n");
	return -1;
}
si_other.sin_family = AF_INET;
si_other.sin_addr.s_addr=inet_addr(ADDRESS);
si_other.sin_port = htons(PORT);

rtrn=sendto(client_fd, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen);
if(rtrn == -1)
{
	perror("sendto error\n");
	return -1;
}
}

#include "header.h"
#define ADDRESS "127.0.0.1"
#define PORT 8080

struct packet *buff;
void hash_coli(void *);
struct packet *pckt,*pt;
int src_port,dest_port;




int main()  
{  
	char buffer[100],buf[200]="\0";
        time_t rawtime;
        struct tm *timeinfo;
        int master_socket , addrlen ,rtrn, new_socket , client_socket[30] ,udp_fd, 
	          max_clients = 30 , activity, i , valread ,max_sd, sd,opt=1;  
        struct sockaddr_in address,client_addr;   
	char hash_timedata[32],client_ip[32]; 
	fd_set readfds;
  
	 memset(client_socket,0,sizeof(client_socket));
	  
	 if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) <= 0)       /*creating the socket fd for tcp */
	 {  
	        perror("TCP socket failed");  
	        return -1;memset(pckt,'\0',sizeof(struct packet));
	 }  
	 if( (udp_fd = socket(AF_INET , SOCK_DGRAM, 0)) <= 0)  			/*creating the socket fd for udp*/
	 {  
	        perror("UDP socket failed");  
	        return -1;
	 }  
	 if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,sizeof(opt)) < 0 )  /*force fully assigning the address to socket fd */
	 {  
	        perror("tcp setsockopt");  
	    	return -1;
	 }  
	 if( setsockopt(udp_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,sizeof(opt)) < 0 )  
	 {
	        perror("udp setsockopt");  
	    	return -1;
    	 }  
	    

	    address.sin_family = AF_INET;						/*filling the server details*/  
	    address.sin_addr.s_addr = inet_addr(ADDRESS); 
	    address.sin_port = htons(PORT);  


	    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)   /*binding the server address and port num with socket_fd */
	    {  
	        perror("tcp bind failed");  
		return -1;
	    }  
	    if (bind(udp_fd,(struct sockaddr *)&address, sizeof(address))<0)  
	    {  
	        perror("udp bind failed");  
		return -1;
	    }  

        

	    if (listen(master_socket, 3) < 0)  				/*mentioning the pending que list for tcp*/
	    {  

	        perror("listen");  
		return -1;
	    }  
        

	    addrlen = sizeof(client_addr);  
	    puts("Waiting for connections ...");  
        
	    while(1)  
	    {  
       
        		FD_ZERO(&readfds);  
			FD_SET(master_socket, &readfds);  
			FD_SET(udp_fd,&readfds);
		        max_sd = udp_fd;  
           		for ( i = 0 ; i < max_clients ; i++)  
		        {  
       
		            sd = client_socket[i];         
		            if(sd > 0)  
                	    {
				FD_SET( sd , &readfds);  
			     }
                            if(sd > max_sd)  
		            {
				    max_sd = sd;  
		            }
			}
		        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);   /*when ever there is an activity at fd with select it ets identified*/
        		if ((activity < 0) && (errno!=EINTR))  
		        {  
		            printf("select error");  
		        }  
      		        if ((FD_ISSET(master_socket, &readfds)))			/*checking whether the activity is at tcp_socket*/
        		{  
		            new_socket =accept(master_socket,(struct sockaddr *)&client_addr, (socklen_t*)&addrlen);
	    		    if(new_socket == -1)  
			    {  
			             perror("tcp_accept");  
			             exit(EXIT_FAILURE);  
			    }  
			    getsockname(new_socket,(struct sockaddr *)&client_addr,(socklen_t *)&addrlen);
			    printf("New connection , socket fd is %d , ip is : %s\n", new_socket ,inet_ntoa(client_addr.sin_addr));  
               	            for (i = 0; i < max_clients; i++)  
			    {  
			               if( client_socket[i] == 0 )  
			                {  
   		                                client_socket[i] = new_socket;  
						printf("Adding to list of sockets as %d\n" , i);  
			                        break;
        			        }  
			    }  
		        }  
			else if((FD_ISSET(udp_fd,&readfds)))  			/*checking whether the activity is at udp_socket*/
			{
				recvfrom(udp_fd,buffer,sizeof(buffer),0,(struct sockaddr *)&client_addr,&addrlen);
				time(&rawtime);
				timeinfo=localtime(&rawtime);
				strcpy(hash_timedata,(char *)asctime(timeinfo));/*time stamp is stored in vrbl*/
				getpeername(sd , (struct sockaddr*)&client_addr,(socklen_t*)&addrlen);
				pckt=(struct packet*)malloc(sizeof(struct packet)); 
				memset(pckt,'\0',sizeof(struct packet));
				strcpy(pckt->time,hash_timedata); 
				pckt->src=(client_addr.sin_addr.s_addr);
				strcpy(pckt->src_addr,inet_ntoa(client_addr.sin_addr));
				strcpy(pckt->dest_addr, inet_ntoa(address.sin_addr));
				pckt->dest=(client_addr.sin_addr.s_addr);
				getsockname(new_socket,(struct sockaddr *)&client_addr,&addrlen);
				pckt->src_port=(ntohs)(client_addr.sin_port);
				pckt->dest_port=ntohs(address.sin_port);
				pckt->protocol=17;
				hash_insert(pckt);
				free(pckt);
				strcpy(client_ip,inet_ntoa(client_addr.sin_addr));
		  		printf("New udp connection , socket fd is %d , ip is : %s\n", udp_fd ,inet_ntoa(client_addr.sin_addr));
				printf("data from the udp client is %s\n",buffer);
		         }
        		for (i = 0; i < max_clients; i++)  
		        {  
		            sd = client_socket[i];  			/*checking whether the activity is at any of the exisintg fd's.*/
              	            if (FD_ISSET( sd , &readfds))  
        		    {  
                	            if ((valread = read( sd , buf,sizeof(buf))) == 0)  
			            {  
			                    getsockname(new_socket,(struct sockaddr *)&client_addr,&addrlen);
			                    getpeername(sd , (struct sockaddr*)&client_addr,(socklen_t*)&addrlen);  
			                    printf("Host disconnected , ip %s\n",inet_ntoa(client_addr.sin_addr));  
			                    close( sd );  
			                    client_socket[i] = 0;  
			   
				     }  
	    	                     else
			             {  
                    
					 
						printf("read\n");
	                    			read(sd,buf,sizeof(buf));  /*waiting for client to read some data*/
						//printf("%s",buf);
						pt=(struct packet *)buf;
						pt->protocol=6;
						pt->src=ntohl(pt->src);
						pt->dest=ntohl(pt->dest);
						printf("%s\n",pt->time);
						if(strcmp(pt->time,"look")==0)	/*for cehcking all the time stamps of a particular entry*/
						{
							hash_lookup((void *)pt);
							memset(pt,0,sizeof(struct packet));		
								break;
						}
						if(strcmp(pt->time,"delete")==0)	/*for deletion a particular entry*/
						{
							hash_del((void *)pt);
							memset(pt,0,sizeof(struct packet));		
								break;
						}
						time(&rawtime);
						timeinfo=localtime(&rawtime);
						rtrn=printf("%s\n",asctime(timeinfo));
						strcpy(buffer,(char *)asctime(timeinfo));
						/*------------------------copying data into packet -----------------------*/
							
						pckt=(struct packet*)malloc(sizeof(struct packet)); 
						memset(pckt,'\0',sizeof(struct packet));						
						strcpy(pckt->time,buffer);
						memset(buffer,'\0',sizeof(buffer));
						strcpy(pckt->src_addr,inet_ntoa(client_addr.sin_addr));
						pckt->src=(client_addr.sin_addr.s_addr);
						strcpy(pckt->dest_addr, inet_ntoa(address.sin_addr));
						pckt->dest=(client_addr.sin_addr.s_addr);
						getsockname(new_socket,(struct sockaddr *)&client_addr,&addrlen);
						pckt->src_port=(ntohs)(client_addr.sin_port);
						pckt->dest_port=ntohs(address.sin_port);
						pckt->protocol=6;
						hash_insert((void *)pckt);
						free(pckt);
						getpeername(sd , (struct sockaddr*)&client_addr,(socklen_t*)&addrlen); 
						strcpy(client_ip,inet_ntoa(client_addr.sin_addr));
							

			                }  
		            }  
	        }  
    }  
        
    return 0;  
}  

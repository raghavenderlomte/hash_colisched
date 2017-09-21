#include "header.h"
#define M 65535   /*max size for the hash table*/





int last,size=5;
struct colisched a[M];
struct colisched *cellar,*temp;
char buffer[]="\0";
int coli_index(struct packet *pt)  
{
	int key1,key2,key;

	key1=((pt->src)&(pt->dest));
	key2=((pt->src_port)&(pt->dest_port));
	key1=(key1+key2+(pt->protocol));
	key=((key1)%MAX);
	key1=abs(key);
	printf("%d",key1);
	return key1;
}

void hash_lookup(void *packt)
{
	int key;
	packt=(struct packet *)packt;
	struct colisched *temp;
	key=coli_index(packt);
        temp=&a[key];
	while(temp->ptr!=NULL)
	{
               temp=temp->ptr;
		printf("data is %s\n",temp->time);
        }
        printf("data in the hash_table is %s\n",temp->time);
}
struct colisched *update_array_size(struct colisched *b)
{
	int inpt;
	struct colisched *rtrn;
	printf("array got filled\nplease enter the size to increase\n");
	scanf("%d",&inpt);
	size=size+inpt;
	rtrn=(struct colisched *)realloc(b,inpt);
	if(rtrn == NULL)
	{
		perror("memor allocation failed\n");
		return  b;
	}
	memset((rtrn+last),'\0',(inpt)*sizeof(struct colisched));
	return rtrn;
}
int gap_coli(struct packet *p,int index)
{
	int first=0,ret;
	while(first != last)
	{
		if(strcmp(cellar[first].time,buffer)==0)
		{
			a[index].ptr=&cellar[first];
			strcpy(cellar[first].time,p->time);
			cellar[first].src=p->src;	
			cellar[first].dest=p->dest;
			cellar[first].src_port=p->src_port;
			cellar[first].dest_port=p->dest_port;
			cellar[first].protocol=p->protocol;
			ret=0;
			return ret;		//successfully inserted in an empty location
		}
		first++;
	}
	ret=1;
	return ret; 			//no empty loation
}
void coli_insert(struct packet *pc,int key)
{
	char buffer[]="\0";

 	static int i=0;
	int ret;
	if(i == 0)
	{
		cellar=(struct colisched *)malloc((size)*sizeof(struct colisched));
		memset(cellar,'\0',size);
		i++;
	}
	/*printf("jst aftr coli iunser\n");*/
	
	if(!strcmp(a[key].time,buffer))
	{
		/*printf("in side if\n");*/
		strcpy(a[key].time,pc->time);
		a[key].src=pc->src;
		a[key].dest=pc->dest;
		a[key].src_port=pc->src_port;
		a[key].dest_port=pc->dest_port;
		a[key].protocol=pc->protocol;
		printf("data at %d is %s\n",key,a[key].time);
		printf("src int val %d\n",a[key].src);
		printf("dest int val %d\n",a[key].dest);
		printf("src port %d\n",a[key].src_port);
		printf("dest port %d\n",a[key].dest_port);
		printf("protocol %d\n",a[key].protocol);
		
	}
	else
	{
		if(a[key].ptr==NULL)
		{
			ret=1;
			if(last == size-1)
			{
			
				ret = gap_coli(pc,key);
				cellar=update_array_size(cellar);
			}
			if(ret == 1)
			{
				strcpy(cellar[last].time,pc->time);
				a[key].ptr=&cellar[last];
				cellar[last].src=pc->src;	
				cellar[last].dest=pc->dest;
				cellar[last].src_port=pc->src_port;
				cellar[last].dest_port=pc->dest_port;
				cellar[last].protocol=pc->protocol;
				printf("data stored at cellar[%d] data %s\n",last,cellar[last].time);
				last++;
			}

		}	
		else
		{
			
			temp=a[key].ptr;
			/*printf("after temp\n"); */
			printf("%s\n",temp->time);
			while(temp->time !=NULL)
			{
				
				if(temp->ptr == 0)
				{	
		       			strcpy(cellar[last].time,pc->time);
					cellar[last].src=pc->src;
		                        cellar[last].dest=pc->dest;
                       			cellar[last].src_port=pc->src_port;
		                        cellar[last].dest_port=pc->dest_port;
		                        cellar[last].protocol=pc->protocol;
					temp->ptr=&cellar[last];
					printf("data stored in cellar[ %d] and data is %s\n",last,cellar[last].time);
					last++;
					if(last == size-1)
					{
						cellar=update_array_size(cellar);
					}
					return;
					
				}	
				
				temp=temp->ptr;
				
			}
		}
	}
}
			
			
			
void hash_insert(void  *packet)
{
packet=(struct packet *)packet;
	int key=0;
	
	key=coli_index(packet);
	
	coli_insert(packet,key);
	
	
}
void  hash_del(void *pac)
{
            char buffer[]="\0";
            struct colisched *temp,*prev;
            pac=(struct packet *)pac;
            int key;
            key=coli_index(pac);
            temp=&a[key];
            prev=&a[key];
            while(strcmp(a[key].time,buffer)!=0)
            {
                    temp=&a[key];
                    prev=&a[key];
                    while(temp->ptr!=NULL)
                    {
	                    prev=temp;
	                    temp=temp->ptr;
		    }
			printf("%s\n",temp->time);
			strcpy(temp->time,buffer);
			prev->ptr=NULL;
			printf("aftrdel=%s\n",temp->time);

	     }
}
	



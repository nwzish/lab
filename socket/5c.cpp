#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(){
int sock;      // client socket discriptor
unsigned int len;
char ch[2]="y";
char ch1[4];

struct sockaddr_in client;
if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){  // client socket is created..
perror("socket: ");
exit(-1);
}

printf("Enter port number\n");
int p; scanf("%d",&p);

client.sin_family=AF_INET;
client.sin_port=htons(p);        // initializing  socket  parameters 
client.sin_addr.s_addr=INADDR_ANY;
//inet_addr("127.0.0.1");
bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 


len=sizeof(struct sockaddr_in);
if((connect(sock,(struct sockaddr *)&client,len))==-1){  //conneting to client
perror("connect: ");
exit(-1);
}

while(1){
	int n;
	printf("enter number :\n");
	scanf("%d",&n);
	
	send(sock,&n,sizeof(n),0);
	while(1){
		int a;
		recv(sock,&a,sizeof(a),0);
		if(a==0) printf(" ");
		else if(a==1) printf("*");
		else if(a==2) printf("\n");
		else if(a==3) break;
		}

	// printf("sum = %d , difference = %d, product = %d, divisio = %f \n",a[0],a[1],a[2],b );
                           // receiving data from client
	printf("\ndo you want to exit...press 'y'\n");


	scanf("%s",ch1);
	//printf("%s\n",ch1);
	//printf("%s\n",ch);

	if((strcmp(ch,ch1))==0){
		close(sock);
		exit(0);
	}

}

}

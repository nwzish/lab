#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <bits/stdc++.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<bits/stdc++.h>
using namespace std;
int main(){
	int ssock,csock;
	// creating server and clinet socket discriptor
	int a,b,c,n;
	unsigned int len;
	int f=4;
	int count1=0;
	struct sockaddr_in server,client; // creating server & client socket object
	if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
	perror("socket: is not created");
	exit(-1);
	}
	
	printf("Enter port number\n");
	int p; scanf("%d",&p);
	server.sin_family=AF_INET;
	server.sin_port=htons(p);
	// initializing server socket parameters..
	server.sin_addr.s_addr=INADDR_ANY;
	//inet_addr("127.0.0.1");
	bzero(&server.sin_zero,0);
	len=sizeof(struct sockaddr_in);
	if((bind(ssock,(struct sockaddr *)&server,len))==-1)
	{ // binding port & IP
	perror("bind: ");
	exit(-1);
	}
	if((listen(ssock,5))==-1)
	{ // listening for client
	perror("listen: ");
	exit(-1);
	}
	if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1)
	{ // accepting connectn
	perror("accept: ");
	exit(-1);
	}
	a=3;
	while(1)
	{
		recv(csock,&n,sizeof(n),0);
		if(n==0)
		c=3;
		else{
		c+=(f*count1);
		count1++;
		}
		send(csock,&c,sizeof(c),0);
		// sending data to client...
		printf("\nSent number is=: %d\n",c);
		}
	close(ssock);
}



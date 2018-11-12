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

void main(){

int ssock,csock;       // creating server and clinet socket discriptor
int a,b,c;
unsigned int len;

struct sockaddr_in server,client;   // creating server & client socket object

if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
	perror("socket: is not created");
	exit(-1);
}

printf("Enter port number\n");
int p; scanf("%d",&p);

server.sin_family=AF_INET;
server.sin_port=htons(p);       // initializing server socket parameters..
server.sin_addr.s_addr=INADDR_ANY;
//inet_addr("127.0.0.1");
bzero(&server.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 


len=sizeof(struct sockaddr_in);

if((bind(ssock,(struct sockaddr *)&server,len))==-1){  // binding port & IP  
	perror("bind: ");
	exit(-1);
}

if((listen(ssock,5))==-1){     // listening for client
	perror("listen: ");                     
	exit(-1);
}


if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1){  // accepting connectn
	perror("accept: ");                         
	exit(-1);
}
while(1){
	char pasw[100] = "moto", reply[100] ="hello",fail[100]="fail";
	char rcv[100],hi[100];
	
	recv(csock,&rcv,sizeof(rcv),0);
	//recv(csock,&hi,sizeof(hi),0);
	printf("hii\n");
	if(strcmp(rcv,pasw)==0)
	send(csock,&reply,sizeof(reply),0);   
	else
	{
		send(csock,&fail,sizeof(fail),0);
	}
	         // sending data to client...	
	
	

}


close(ssock);









}

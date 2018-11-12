#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<bits/stdc++.h>
using namespace std;
int main(){
	int sock; // client socket discriptor
	int a,b,c,i,n;
	unsigned int len;
	char ch[3]="ex";
	char ch1[3];
	struct sockaddr_in client;
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){ // client socket is created..
	perror("socket: ");
	exit(-1);
	}
	client.sin_family=AF_INET;
	client.sin_port=htons(10000);
	// initializing socket parameters
	client.sin_addr.s_addr=INADDR_ANY;
	//inet_addr("127.0.0.1");
	bzero(&client.sin_zero,0);
	len=sizeof(struct sockaddr_in);
	if((connect(sock,(struct sockaddr *)&client,len))==-1){ //conneting to client
	perror("connect: ");
	exit(-1);
	}
	while(1){
	printf("Enter Number:\n");
	scanf("%d",&n);
	send(sock,&n,sizeof(n),0);
	recv(sock,&c,sizeof(c),0);
	printf("Number sent is %d\n",c);
	// receiving data from client
	printf("\nDo you want to exit...press 'ex'\n");
	scanf("%s",ch1);
	//printf("%s\n",ch1);
	//printf("%s\n",ch);
	if((i=strcmp(ch,ch1))==0){
	close(sock);
	exit(0);
	}
}
}


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<bits/stdc++.h>
using namespace std;

struct Student
{
int name;
int age;
int std;
int section;
int pin;
};
int main()
{
	struct Student data[10];
	int i;
	for(i=0;i<10;i++)
	{
	data[i].age=i+10;
	data[i].std=i+1;
	data[i].section=i;
	data[i].name=i+2;
	data[i].pin=i*i;
	}
	int ssock,csock;
	// creating server and clinet socket discriptor
	int a,b,c;
	unsigned int len;
	char ch[1];
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
	while(1)
	{
		recv(csock,&a,sizeof(a),0);
		printf("\nClient: Send Details for roll no. %d",a);
		a--;
		struct Student temp=data[a];
		send(csock,&temp,sizeof(temp),0);
		printf("\nRecord of Student With Roll No %d is sended.",a+1);
	}
	close(ssock);
}


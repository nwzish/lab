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
	int sock; // client socket discriptor
	int a,b,c,i;
	unsigned int len;
	char ch[3]="y";
	char ch1[3];
	struct sockaddr_in client;
	if( (sock=socket(AF_INET,SOCK_STREAM,0))==-1 )
	{
	// client socket is created..
	perror("socket: ");
	exit(-1);
	}
	
	printf("Enter port number\n");
	int p; scanf("%d",&p);
	
	client.sin_family=AF_INET;
	client.sin_port=htons(p);
	// initializing socket parameters
	client.sin_addr.s_addr=INADDR_ANY; //inet_addr("127.0.0.1");
	bzero(&client.sin_zero,0);
	len=sizeof(struct sockaddr_in);
	if( (connect(sock,(struct sockaddr *)&client,len))==-1)
	{
	//conneting to client
	perror("connect: ");
	exit(-1);
	}
	while(1)
	{
		printf("\nServer:");
		printf(" Enter Roll No. - ");
		scanf("%d",&a);
		send(sock,&a,sizeof(a),0);
		struct Student temp;
		recv(sock,&temp,sizeof(temp),0);
		printf("\nName is -> %d",temp.name);
		printf("\nAge is -> %d",temp.age);
		printf("\nClass is -> %d",temp.std);
		printf("\nSection is -> %d",temp.section);
		printf("\nPinCode is -> %d",temp.pin);
		printf("\nServer: Do you want to exit...press 'y' else press any key\n");
		scanf("%s",ch1);
		if((i=strcmp(ch,ch1))==0)
		{
		printf("\nServer: GOT it!\n");
		close(sock);
		exit(0);
	}
}
}


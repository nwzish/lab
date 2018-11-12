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
int main()
{
char s[512],arr[26]={0};
int sock,dp[100];
int a,b,c,d,i,j;
unsigned int len;
char ch[4]="y",ch2;
char ch1[4];
struct sockaddr_in client;
if( (sock=socket(AF_INET,SOCK_
{
// client socket is created..
perror("socket: ");
exit(-1);
}

printf("Enter port number\n");
	int p; scanf("%d",&p);
client.sin_family=AF_INET;
client.sin_port=htons(p);
client.sin_addr.s_addr=INADDR_
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
        cout<<"type the word\n";
         cin>>s;
        send(sock,&s,sizeof(s),0);
    //    send(sock,&b,sizeof(b),0);
        cout<<"maximum repeating character is\n";
        recv(sock,&ch2,sizeof(ch2),0);
        cout<<ch2<<"\n";

        printf("\n-----------terminal exit chatting--------\n1.y\n2.no\
        scanf("%s",ch1);
        if((j=strcmp(ch,ch1))==0)
        {
        printf("\nServer: GOT it!\n");
        close(sock);
        exit(0);
        }
    }
}



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
char s[512],ch2;
int ssock,csock,arr[26]={0},ma=-3;
int dp[100];
int a,b,c,j,d,fib1,fib2;
unsigned int len;
struct sockaddr_in server,client;
if((ssock=socket(AF_INET,SOCK_
{
perror("socket: is not created");
exit(-1);
}

printf("Enter port number\n");
	int p; scanf("%d",&p);
server.sin_family=AF_INET;
server.sin_port=htons(p);
server.sin_addr.s_addr=INADDR_
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
          recv(csock,&s,sizeof(s),0);
      cout<<"recieved string is "<<s<<"\n";
      int i=0;
        while(s[i]!='\0')
        {
            //cout<<s[i]<<" ";
            arr[s[i]-'a']++;
            i++;
        }
//cout<<"out of loop\n";
for(int i=0;i<26;i++)
{
if(arr[i]>ma)
{
    ch2='a'+i;
    ma=arr[i];
}
}

    
    send(csock,&ch2,sizeof(ch2),0)
    
    }
close(ssock);
}


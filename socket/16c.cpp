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

//client code

void main(){
int sock;      // client socket discriptor
int a,b,c,i;
unsigned int len;
char ch[2]="y";
char ch1[3];

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
printf("enter pass to say hii\n");
char pasw[100] ;
scanf("%s",pasw);

send(sock,&pasw,sizeof(pasw),0);
//send(sock,&b,sizeof(b),0);       // sending data back to client...
char rec[100];
recv(sock,&rec,sizeof(rec),0);
printf("%s\n",rec);
                           // receiving data from client
printf("\ndo you want to exit .. press 'y'\n");


scanf("%s",ch1);
if((i=strcmp(ch,ch1))==0){
close(sock);
exit(0);
}


}

}

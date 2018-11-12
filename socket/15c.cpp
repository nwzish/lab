#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>


int main(){
int sock;      // client socket discriptor

unsigned int len;

struct sockaddr_in client;
if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){  // client socket is created..
perror("socket: ");
exit(-1);
}

client.sin_family=AF_INET;
client.sin_port=htons(10000);        // initializing  socket  parameters
client.sin_addr.s_addr=INADDR_ANY;
//inet_addr("127.0.0.1");
bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'..


len=sizeof(struct sockaddr_in);
if((connect(sock,(struct sockaddr *)&client,len))==-1){  //conneting to client
perror("connect: ");
exit(-1);
}

char buffer[255];
FILE *fp;
fp=fopen("first.txt","r");
int wordCount = 0;
char c;

while((c=getc(fp))!=EOF)
{
	fscanf(fp,"%s",buffer);
	if(isspace(c)||c == '\t')
		wordCount++;
}

write(sock,&wordCount,sizeof(int));
rewind(fp);

char ch;

while(ch!=EOF)
{
	fscanf(fp,"%s",buffer);
	write(sock,buffer,255);
	ch = fgetc(fp);
}

printf("file has been successfully uploaded\n");

close(sock);
return 0;
}


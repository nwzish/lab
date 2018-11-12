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

struct dic{
	char w[30];
	char m[30];

};
int main(){
	int ssock,csock; // creating server and clinet socket discriptor
	
	unsigned int len;
	struct sockaddr_in server,client; // creating server & client socket object
	if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket: is not created");
		exit(-1);
	}
	
	printf("Enter port number\n");
	int p; scanf("%d",&p);
	server.sin_family=AF_INET;
	server.sin_port=htons(p); // initializing server socket parameters..
	server.sin_addr.s_addr=INADDR_ANY;
	//inet_addr("127.0.0.1");
	bzero(&server.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'..
	len=sizeof(struct sockaddr_in);
	if((bind(ssock,(struct sockaddr *)&server,len))==-1){ // binding port & IP
		perror("bind: ");
		exit(-1);
	}
	if((listen(ssock,5))==-1){ // listening for client
	perror("listen: ");
	exit(-1);
	}
	if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1){ // accepting connectn
		perror("accept: ");
		exit(-1);
	}
	int di = 0;
	struct dic dict[200];
	
	//dict[0].w = "TV";
	//dict[0].m = "Television";
	while(1){
		char w[30];
		 
		recv(csock,w,sizeof(w),0);
		int res = -1,i;
		for(i=0;i<=di;i++){
			if(strcmp(w,dict[i].w)==0){
				res = i; break;
			}
		}
		int rep;
		if(res==-1){
			rep = 1;
			send(csock,&rep,sizeof(rep),0);
			char meaning[30];
			di++;
			recv(csock,&dict[di],sizeof(dict[di]),0);
			//di++;
			//dict[di].w = w;
			//dict[di].m = meaning;
			printf("Word added\n");
		
		}
		else {
			rep = 0;
			send(csock,&rep,sizeof(rep),0);
			send(csock,dict[res].m,sizeof(dict[res].m),0);
			printf("Meaning of %s sent\n",w);
		}
		
		//send(csock,&j,sizeof(j),0);
		//send(csock,a,sizeof(a),0);
		 // sending data to client...
		//printf("\nPrime factorization of %d sent\n",n);
}
close(ssock);
}

    

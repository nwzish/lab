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

struct leave{
	int tl;
	int bl;
	int el;

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
	struct leave l[200];
	int i;
	for(i=0;i<200;i++){
		l[i].tl=0; l[i].bl=20; l[i].el=0;
	}
	
	//dict[0].w = "TV";
	//dict[0].m = "Television";
	while(1){
	
		int c; recv(csock,&c,sizeof(c),0);
		int f;
		if(c>=200){f=1;
		send(csock,&f,sizeof(f),0); continue;
		}
		else {
		f=0;
		send(csock,&f,sizeof(f),0);
		}
		int ln;
		recv(csock,&ln,sizeof(ln),0);
		printf("%d\n", ln);
		l[c].tl+=ln; printf("%d\n",l[c].tl);
		l[c].bl-=ln;
		if(l[c].bl<0){
			l[c].el-=l[c].bl; l[c].bl=0;
		}
		
		send(csock,&l[c],sizeof(l[c]),0);
		
		printf("Information sent\n");
		
		
		
		
		
		//send(csock,&j,sizeof(j),0);
		//send(csock,a,sizeof(a),0);
		 // sending data to client...
		//printf("\nPrime factorization of %d sent\n",n);
}
close(ssock);
}

    

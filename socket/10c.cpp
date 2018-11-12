#include <bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
struct leave{
	int tl;
	int bl;
	int el;

};
int main(){
	int sock; 
	unsigned int len;
	char ch[2]="y", ch1[2];
	
	struct sockaddr_in client;
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket: ");
		exit(-1);
	}
	
	printf("Enter port number\n");
	int p; scanf("%d",&p);
	
	client.sin_family = AF_INET;
	client.sin_port = htons(p);
	client.sin_addr.s_addr = INADDR_ANY;
	
	bzero(&client.sin_zero,0);
	
	len = sizeof(struct sockaddr_in);
	if((connect(sock,(struct sockaddr *)&client, len))==-1){
		perror("connect: ");
		exit(-1);
		
	}
	
	while(1){
	
		printf("Enter Employee number\n");
		int c ; scanf("%d",&c);
		send(sock,&c,sizeof(c),0);
		int f;
		recv(sock,&f,sizeof(f),0);
		if(f){
			printf("retry\n");
			continue;
		}
		printf("Enter no of leaves you want to take\n");
		int l; scanf("%d",&l);
		send(sock,&l,sizeof(l),0);
		
		struct leave r;
		recv(sock,&r,sizeof(r),0);
		
		printf("Total leave: %d\nBalance Leave: %d\nExtra Leave: %d\n",r.tl,r.bl,r.el); 
		
		
		
		printf("\n do you want to exit  press 'y'\n");
		
		
		scanf("%s",ch1);
		
		if((strcmp(ch,ch1))==0){
		close(sock);
		exit(0);
	
		}
	}
	
}

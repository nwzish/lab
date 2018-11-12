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
struct dic{
	char w[100];
	char m[100];

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
	
		printf("Do you want to add quetion to dictionary enter 1\n");
		int c ; scanf("%d",&c);
		if(c==1){
			printf("Enter question\n");
			struct dict q;
			scanf("%s",&q.w);
			printf("Enter answer\n");
			scanf("%s",&q.m);
			send(sock,&q,sizeof(q);0);
			printf("Question added\n");
		
		
		
		}
		else{
		printf("enter question:\n");
		struct dic e;
		char w[30];
		scanf("%s",&e.w);
		//gets(e.w);
		
		
		send(sock,e.w,sizeof(e.w),0);
		//send(sock,&a,sizeof(b),0);
		int rep;
		recv(sock,&rep,sizeof(rep),0);
		if(rep){
			printf("question not present in dictionary Enter Meaning to add\n");
			
		
		}
		else{
			char m[30];
			recv(sock,m,sizeof(m),0);
			printf("answer of %s is %s\n",e.w,e.m);
		
		}
		
		}
		
		
		printf("\n do you want to exit  press 'y'\n");
		
		
		scanf("%s",ch1);
		
		if((strcmp(ch,ch1))==0){
		close(sock);
		exit(0);
	
		}
	}
	
}

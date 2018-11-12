#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
void main() {
  int i;
  unsigned int len;
  int sock;
  struct sockaddr_in client;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) ==
      -1) {  // client socket is created..
    perror("socket: ");
    exit(-1);
  }

  printf("Enter port number\n");
	int p; scanf("%d",&p);
  client.sin_family = AF_INET;
  client.sin_port = htons(p);  // initializing  socket  parameters
  client.sin_addr.s_addr = INADDR_ANY;
  // inet_addr("127.0.0.1");
  bzero(&client.sin_zero,
        0);  // appending 8 byte zeroes to 'struct sockaddr_in', to make it
             // equal in size with 'struct sockaddr'..

  len = sizeof(struct sockaddr_in);
  if ((connect(sock, (struct sockaddr *)&client, len)) ==
      -1) {  // conneting to client
    perror("connect: ");
    exit(-1);
  }
  int n, res, k;
  while (1) {
    printf("Enter the number: ");
    scanf("%d", &n);
    send(sock, &n, sizeof(n), 0);
    recv(sock, &res, sizeof(res), 0);
    for(k=0; k<res; k++){
        recv(sock, &n, sizeof(n), 0);
        printf("%d  ", n);
    }
    printf("\ndo you want to exit...press 'y' or 'n'\n");
    char ip; scanf(" %c", &ip);
    if(ip=='y') {
      close(sock); exit(0);
    }
  }
}

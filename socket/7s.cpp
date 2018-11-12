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
  unsigned int len;
  int ssock, csock;  // creating server and clinet socket discriptor
  struct sockaddr_in server, client;  // creating server & client socket object
  if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket: is not created");
    exit(-1);
  }
  
  printf("Enter port number\n");
  int p; scanf("%d",&p);
  server.sin_family = AF_INET;
  server.sin_port = htons(p);  // initializing server socket parameters..
  server.sin_addr.s_addr = INADDR_ANY;
  // inet_addr("127.0.0.1");
  bzero(&server.sin_zero,
        0);  // appending 8 byte zeroes to 'struct sockaddr_in', to make it
             // equal in size with 'struct sockaddr'..

  len = sizeof(struct sockaddr_in);

  if ((bind(ssock, (struct sockaddr *)&server, len)) ==
      -1) {  // binding port & IP
    perror("bind: ");
    exit(-1);
  }
  if ((listen(ssock, 5)) == -1) {  // listening for client
    perror("listen: "); exit(-1);
  }

  if ((csock = accept(ssock, (struct sockaddr *)&client, &len)) ==
      -1) {  // accepting connectn
    perror("accept: ");
    exit(-1);
  }
  int n, arr[100]={0}, k, j;
    while (1) {
        int count =0;
        recv(csock, &n, sizeof(n), 0);
        for(k=2; k<=n; k++){
            int flag=0;
            for(j=2; j<k; j++){
                if(k%j==0){
                    flag=1;
                    break;
                }
            }
            if(flag==0){
                while(n%k==0 && n>=2){
                    arr[count]=k;
                    count++;
                    n = n/k;
                }
            }
        }
        send(csock, &count, sizeof(count), 0);
        for(k=0; k<count; k++){
            send(csock, &arr[k], sizeof(arr[k]), 0);
        }
    }
    close(ssock);
}

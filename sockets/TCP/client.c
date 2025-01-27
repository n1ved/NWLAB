#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


void main(){
  int client;
  char buffer[1024];
  struct sockaddr_in server_addr;
  socklen_t addr_size;

  client = socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port   = htons(6265);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  connect(client,(struct sockaddr*)&server_addr,sizeof(server_addr));

  printf("[info] Sending data ...\n");

  strcpy(buffer,"Hi this is client\n");
  send(client,buffer,19,0);
  recv(client,buffer,1024,0);
  printf("[recv] Recieved : %s\n",buffer);

  close(client);
}

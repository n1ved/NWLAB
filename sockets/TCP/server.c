#include <stdio.h>
#include <sys/socket.h>   //to use sockets
#include <netinet/in.h>   //contains definitions for IP family
#include <string.h>
#include <arpa/inet.h>    //contains internet operations
#include <unistd.h>       //POSIX system APIs

void main(){
  int server,client;
  char buffer[1024];

  struct sockaddr_in server_addr;
  struct sockaddr_storage store;

  socklen_t addr_size;


  server = socket(AF_INET,SOCK_STREAM,0);
  //AF_INET stands for Address FAMILY : IPV4
  //SOCK_STEAM for TCP
  
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(6265);
  server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");


  bind(server,(struct sockaddr*)&server_addr,sizeof(server_addr));
  //File descriptor , server address pointer , address length

  if(listen(server,5) == 0)
    printf("[info] Listening\n");
  else
    printf("[err]  Cannot Listen\n");

  client = accept(server,(struct sockaddr*)&store,&addr_size);
  //socket descriptor , client storage address , size of address structure
  
  recv(client,buffer,1024,0);
  printf("[recv] Data Recieved : %s\n",buffer);


  strcpy(buffer,"Hi this is server\n");
  printf("[info] Sending data\n");
  send(client,buffer,19,0);


  close(client);
  close(server);
}


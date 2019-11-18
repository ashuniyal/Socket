#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h> 

int main(){
  int serverSocket, newSocket;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  serverSocket = socket(AF_INET,SOCK_STREAM,0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8080);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  if(listen(serverSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");
  while(1)
  {
   	 addr_size=sizeof serverStorage;
     newSocket = accept(serverSocket,(struct sockaddr *)&serverStorage,&addr_size);
	 int i=0;
	 for(i=0;i<5;i++)
	 {
 		 printf("Value--->%d \n",i);
	 }
	 close(newSocket);
  }
  return 0;
}

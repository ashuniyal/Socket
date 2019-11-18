#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h> 
#include<pthread.h>


void * dealing(void *clintsock)
{
	int sock=*((int*)clintsock);
	int i;
	for(i=0;i<5;i++)
	{
		printf("Socket %d--->%d \n",sock,i);
	}
	close(sock);
	pthread_exit(NULL);
}

int main(){
  int serverSocket, newSocket;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8080);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  if(listen(serverSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");
  pthread_t tid[5];
  int i = 0;
  while(1)
  {
     addr_size = sizeof serverStorage;
     newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
	 if( pthread_create(&tid[i], NULL, dealing, &newSocket) != 0 )
		  printf("Failed to create thread\n");
	 i++;        
	  if( i >= 5)
	  {
	    i = 0;
	    while(i < 5)
	    {
	      pthread_join(tid[i++],NULL);
	    }
	    i = 0;
	  }
  }
  return 0;

}

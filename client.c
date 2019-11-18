#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include<pthread.h>

void * clientThread()
{
	int clso=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addre;
	socklen_t addr_size;
	addre.sin_family = AF_INET;
    addre.sin_port = htons(8080);
	addre.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(addre.sin_zero,'\0',sizeof addre.sin_zero);
	addr_size=sizeof addre;
	connect(clso,(struct sockaddr *)&addre,addr_size);
	sleep(20);	
	close(clso);
	pthread_exit(NULL);
}


int main(){

  int i = 0;
  pthread_t tid[6];
  while(i<5)
  {
    if( pthread_create(&tid[i], NULL, clientThread,NULL) != 0 )
           printf("Failed to create thread\n");
    i++;
  }
  sleep(20);
  i = 0;
  while(i<5)
  {
     pthread_join(tid[i++],NULL);
  }
  return 0;
}

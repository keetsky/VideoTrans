
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netinet/in.h>

#include <cv.h>



int socketfd=-1;
extern "C" int imagesend_c();
 int main(int argc,char **argv)
 {


	char *servInetAddr = "192.168.1.189";
 	//int socketfd;
 	struct sockaddr_in sockaddr;

 	int n;

 
 	socketfd = socket(AF_INET,SOCK_STREAM,0);
 	memset(&sockaddr,0,sizeof(sockaddr));
 	sockaddr.sin_family = AF_INET;
 	sockaddr.sin_port = htons(6666);
 	inet_pton(AF_INET,servInetAddr,&sockaddr.sin_addr);
 	if((connect(socketfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr))) < 0 )
 	{
		 printf("connect error %s errno: %d\n",strerror(errno),errno);
 		exit(0);
 	}

 	printf("send message to server\n");




	sleep(5);//等待10秒发后送
	imagesend_c();
 	close(socketfd);
 	printf("exit\n");
 	exit(0);
	return 0;

 }


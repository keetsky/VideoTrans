
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
#include<highgui.h>
#define MAXLINE 640*480*4


extern int connfd;

int imagereceive_c()
{
	printf("dsss:%d\n",connfd);
	while(1)
	{
	IplImage *p = imagereceive();
cvShowImage("123",p);
 cvWaitKey(1);
	}

}

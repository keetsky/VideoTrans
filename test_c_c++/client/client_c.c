/********************************
	zhanwang zhang
	keetsky@163.com
	2017.03.20
	电子哨兵项目：视频压缩实时传输
	客户端，发送视频

*********************************/




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
extern int socketfd;

int imagesend_c()
{
	printf("dsss:%d\n",socketfd);
	CvCapture *capture = cvCreateCameraCapture(0);
	IplImage *frame;
	while(1)
	{
	frame = cvQueryFrame(capture);
	
	imagesend(frame);
	}	
	return 0;
}


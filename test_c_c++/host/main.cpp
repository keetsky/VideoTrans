//http://www.itdadao.com/articles/c15a703614p0.html
/********************************
	zhanwang zhang
	keetsky@163.com
	2017.03.20
	电子哨兵项目：视频压缩实时传输
	主机端接受视频
调试原则：分别对主机和客户端前一或二次循环进行数据对比；如果相同表示发送完整
*********************************/

#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <fstream>
#include <cv.h>
#include <vector>
#include<iostream>
#include<time.h>
#define MAXLINE 640*480*4
using namespace std ;
using namespace cv;


int connfd=-1;

extern "C" int imagereceive_c();
 int main(int argc,char **argv)
 {
 	int listenfd;
	//int connfd;
 	struct sockaddr_in sockaddr;
 	
 	int n;
 
 	memset(&sockaddr,0,sizeof(sockaddr));
 
 	sockaddr.sin_family = AF_INET;
 	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 	sockaddr.sin_port = htons(6666);
 
 	listenfd = socket(AF_INET,SOCK_STREAM,0);
 
 	bind(listenfd,(struct sockaddr *) &sockaddr,sizeof(sockaddr));
 
 	listen(listenfd,1);

 
 	printf("Please wait for the client information\n");

 	if((connfd = accept(listenfd,(struct sockaddr*)NULL,NULL))==-1)
 	{
 	printf("accpet socket error: %s errno :%d\n",strerror(errno),errno);
	return 0;	
 	}
	else
		printf("accpet sucess\n");



	imagereceive_c();


	close(connfd);
 	close(listenfd);
	printf("exit\n");
	exit(0);
	return 0;



 
 }





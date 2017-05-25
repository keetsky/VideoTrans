//http://www.itdadao.com/articles/c15a703614p0.html    http://blog.csdn.net/neicole/article/details/7459021   http://www.cnblogs.com/Fightingbirds/p/3934264.html  http://blog.chinaunix.net/uid/24977843/cid-24983-list-1.html
/********************************
	zhanwang zhang
	keetsky@163.com
	2017.03.20
	电子哨兵项目：视频压缩实时传输
	主机端接受视频
调试原则：分别对主机和客户端前一或二次循环进行数据对比；如果相同表示发送完整
遗留问题：client断开后无法销毁图像窗口，虽然不影响程序运行
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
//#include<time.h>
#define MAXLINE 640*480*4
using namespace std ;
using namespace cv;
 int main(int argc,char **argv)
 {
	//startWindowThread();
 	int listenfd,connfd;
 	
 	uchar buff[MAXLINE]={'\0'};
	memset(buff,0, MAXLINE);
 	int n;
 
 	listenfd = socket(AF_INET,SOCK_STREAM,0);
  	if(listenfd < 0)
	{
        	printf("创建TCP套接字失败\n");
        	exit(-1);
    	}
	else
	{
        	printf("创建套接字成功\n");
    	}
	struct sockaddr_in sockaddr;
 	memset(&sockaddr,0,sizeof(sockaddr));
        bzero(&sockaddr,sizeof(struct sockaddr_in));	
 	sockaddr.sin_family = AF_INET;
 	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 	sockaddr.sin_port = htons(6666); 	
 	if(bind(listenfd,(struct sockaddr *) &sockaddr,sizeof(sockaddr))!=0)
	{
        	perror("绑定ip地址、端口号失败\n");
        	exit(-1);			
	}	
	else
	{
	        printf("绑定ip地址,端口号\n");
	}
 
 	if(listen(listenfd,1)!=0)
	{
      		printf("开启监听失败\n");
        	exit(-1);
    	}
	else
	{
	        printf("开启监听成功\n");
   	}
 
 	printf("Please wait for the client information\n");
/*
 	if((connfd = accept(listenfd,(struct sockaddr*)NULL,NULL))==-1)
 	{
 	printf("accpet socket error: %s errno :%d\n",strerror(errno),errno);
	return 0;	
 	}
	else
		printf("accpet sucess\n");
*/	
 	while(true)   
	 {      	
		struct sockaddr_in client_addr;
		socklen_t length=sizeof(client_addr);
		connfd=accept(listenfd,(struct sockaddr*)&client_addr,&length);
		if(connfd==-1)
		{
			perror("accept error!\n");
			//continue;		
		}
		else
		{
			printf("connected the client! %s:%d\n",inet_ntoa(client_addr.sin_addr),client_addr.sin_port);
		}	
		char s[20]={0};
		Mat show;
		int framelen;
		Mat frame;
		namedWindow("received image",CV_NORMAL);
		while(1)
		{
			int recvlen=recv(connfd,s,15,0);
			if(recvlen<=0)
				{
				perror("recv error! client may be disconented!\n");
				break;
				}
			framelen=atoi(s);//接受待接受图像数据的长度
		//	printf("the received buffsize :%d\n",framelen);
			vector<uchar> rebuff;
			int bytes=0;
			for(int k=0;k<framelen;k+=bytes)//将接受的数据全部放入buff数组中
			{
	 			bytes=recv(connfd,&buff[0]+k,framelen-k,0);//每次能够接受数据的长度，不同电脑接受数据长度不一样
			//	printf("bytes:%d\n",bytes);
				if(bytes==0)
				break;
			}
	 
			//printf("n:%d\n",n);
			size_t i=0;
			for(i=0; i<framelen;i++)
			{
				rebuff.push_back(buff[i]);
				//printf("%u\n",buff[i]);
			}

			frame=imdecode(Mat(rebuff),CV_LOAD_IMAGE_ANYCOLOR);
			//send(connfd,"12.2",sizeof(12.2),0);
			imshow("received image",frame);
		
			//cout<<"next frame：\n";
			waitKey(1);
		}
		//break;
	//bzero(buff,MAXLINE);

//	destroyWindow("received image");		
	destroyAllWindows();


 	close(connfd);

 	}
	
 	close(listenfd);

 }





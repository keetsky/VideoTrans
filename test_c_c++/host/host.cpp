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
 int main(int argc,char **argv)
 {
 	int listenfd,connfd;
 	struct sockaddr_in sockaddr;
 	uchar buff[MAXLINE]={'\0'};
	memset(buff,0, MAXLINE);
 	int n;
 
 	memset(&sockaddr,0,sizeof(sockaddr));
 
 	sockaddr.sin_family = AF_INET;
 	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 	sockaddr.sin_port = htons(6666);
 
 	listenfd = socket(AF_INET,SOCK_STREAM,0);
 
 	bind(listenfd,(struct sockaddr *) &sockaddr,sizeof(sockaddr));
 
 	listen(listenfd,1);

 
 	printf("Please wait for the client information\n");
 	char s[20]={0};
	Mat show;
	int framelen;
 	if((connfd = accept(listenfd,(struct sockaddr*)NULL,NULL))==-1)
 	{
 	printf("accpet socket error: %s errno :%d\n",strerror(errno),errno);
	return 0;	
 	}
	else
		printf("accpet sucess\n");
	
	Mat frame;
   cout<<"begin\n";
	//clock_t start,finish;
	//double duration;
  
 	while(true)   //每次循环表示对一帧（图）的数据处理
	 { 
		   
	//cout<<"begin\n";
	/*
		vector<uchar> rebuff;
		recv(connfd,s,15,0);
		framelen=atoi(s);
		printf("the received buffsize :%d\n",framelen);
	 	int n=recv(connfd,buff,framelen,0);
		printf("n:%d\n",n);
		
		
		size_t i=0;
		for(i=0; i<framelen;i++)
		{
			rebuff.push_back(buff[i]);
			//printf("%u\n",buff[i]);
		}
		
		//Mat re=Mat(rebuff);
		frame=imdecode(Mat(rebuff),CV_LOAD_IMAGE_ANYCOLOR);
		imshow("received image",frame);
		cout<<"next frame：\n";
		waitKey(30);

*/


		
		recv(connfd,s,15,0);
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
/*
		ofstream out("filerec.txt",ofstream::out);//将数据写入文件中
		int j=0;
		for(;j<rebuff.size();j++)
		{
			out<<j<<":"<<(int)rebuff.at(j);
			out<<"\n";
			}
		printf("the last 3 number :%d,%d,%d\n",rebuff[j-1],rebuff[j-2],rebuff[j-3]);
		out.close();
*/
		//Mat re=Mat(rebuff);
		frame=imdecode(Mat(rebuff),CV_LOAD_IMAGE_ANYCOLOR);
		imshow("received image",frame);
	//	cout<<"next frame：\n";
		waitKey(1);

		//break;







	//	finish=clock();
	//	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	//	printf("%fsecondas:\n",duration);	
		//break;	
		//Mat re=Mat(rebuff);
		//Mat frame=imdecode(re,CV_LOAD_IMAGE_COLOR);
		//imshow("jpg",frame);
		//waitKey(1);
	
/**	for(int i=0;i<=640*480;i++)
	  	rebuff.push_back(buff[i]);
  
 	 //buff[n] = '\0';
	 Mat img(640,480,CV_8UC3,buff);

         show= imdecode(rebuff,CV_LOAD_IMAGE_COLOR); 
        // imshow("jpg",show); 
 	printf("recv msg from client:%s",buff);
*/
 	
 	}
	close(connfd);
 	close(listenfd);
 }





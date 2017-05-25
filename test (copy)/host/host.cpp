//http://www.itdadao.com/articles/c15a703614p0.html
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
//#include<time.h>
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

	//clock_t start,finish;
	//double duration;
 	while(true) 
	 {      
	
	//	start=clock();
		vector<uchar> rebuff;
		recv(connfd,s,15,0);
		framelen=atoi(s);
		printf("the received buffsize :%d\n",framelen);
	 	int n=recv(connfd,buff,framelen,0);
		printf("n:%d\n",n);
		//printf("%s",rebuff);
		
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





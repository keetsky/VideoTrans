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

const size_t MAXLINE=640*480*4;
uchar buff[MAXLINE]={'\0'};
using namespace std ;
using namespace cv;

extern int connfd;
Mat frame;
IplImage pImg;
extern "C" IplImage* imagereceive()
{
	
	memset(buff,0, MAXLINE);
 	char s[20]={0};
	Mat show;
	int framelen;
	
	//Mat frame;
	
		
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

		}

		frame=imdecode(Mat(rebuff),CV_LOAD_IMAGE_ANYCOLOR);
		pImg = IplImage(frame);
		// IplImage *p = cvCreateImage(cvSize(pImg.width,pImg.height),IPL_DEPTH_8U,3);
		//cvCopy(&pImg,p);
		
		
		return &pImg;

		//imshow("received image",frame);
		

		waitKey(1);


}

/********************************
	zhanwang zhang
	keetsky@163.com
	2017.03.20
	电子哨兵项目：视频压缩实时传输
	客户端，发送视频

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


using namespace std ;
using namespace cv;
//#define MAXLINE 640*480*4
const size_t MAXLINE=640*480*4;
uchar recvline[MAXLINE], sendline[MAXLINE];

//VideoCapture capture(0);
extern int socketfd;
extern "C" int imagesend(IplImage *img)
{



        	
	memset(sendline,0, MAXLINE);
	Mat image(img),left,left2;
	//capture.retrieve(image);
	vector<uchar> buff;
        vector<int> param= vector<int>(2); 
        param[0]=CV_IMWRITE_JPEG_QUALITY; 
        param[1]=80;
	char s[20]={0};


		//if (!capture.isOpened())
			//return 0;

		//capture >> image;
                left=Mat(image,cv::Rect(0,0,640,480));
                cv::imshow("send image",left);
		cv::waitKey(1000/25);
                imencode(".jpg",left,buff,param);
		int bufflen=buff.size();

		sprintf(s,"%d",bufflen);
		send(socketfd,s,15,0);
		

		vector<char>::size_type i=0;
		for(i=0;i!=buff.size();++i)
		{
			sendline[i]=buff[i];

		}

		int n=send(socketfd,(const char*)(&sendline),buff.size(),0);

        

	
 }


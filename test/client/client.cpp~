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
 #define MAXLINE 640*480*4
 int main(int argc,char **argv)
 {
	char *servInetAddr = "192.168.1.148";
 	int socketfd;
 	struct sockaddr_in sockaddr;
        uchar recvline[MAXLINE], sendline[MAXLINE];
	memset(sendline,0, MAXLINE);
 	int n;
 /*
 	if(argc != 2)
 	{
 		printf("client <ipaddress> \n");
 		exit(0);
 	}
*/
 
 	socketfd = socket(AF_INET,SOCK_STREAM,0);
	if(socketfd<0)
	{
		printf("creat TCP connetion words fail！\n");
		exit(0);
	}
 	memset(&sockaddr,0,sizeof(sockaddr));//bzero(&sockaddr,sizeof(struct sockaddr_in));
 	sockaddr.sin_family = AF_INET;
 	sockaddr.sin_port = htons(6666);
 	inet_pton(AF_INET,servInetAddr,&sockaddr.sin_addr);
	//sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");

 	if((connect(socketfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr))) < 0 )
 	{
		 printf("connect error %s errno: %d\n",strerror(errno),errno);
 		exit(0);
 	}
	else
	{
 		printf("connet success, send message to server! \n");
		printf("connected the client! %s:%d\n",inet_ntoa(sockaddr.sin_addr),sockaddr.sin_port);
	}
 	//fgets(sendline,1024,stdin);
        	
	VideoCapture capture(0);
	Mat image,left,left2;
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 1920);  
   	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 1080); 
	namedWindow("send image",CV_NORMAL); 
	capture.retrieve(image); //>> image;
	 vector<uchar> buff;
       vector<int> param= vector<int>(2); 
        param[0]=CV_IMWRITE_JPEG_QUALITY; 
        param[1]=80;//default(95) 0-100 
	char s[20]={0};

        while(true)
	{
		if (!capture.isOpened())
			return 0;

		capture >> image;
	resize(image,image,Size(640,480),INTER_AREA);
                //left=Mat(image,cv::Rect(0,0,640,480));
		left=image;
	//	cout<<left.cols<<" "<<left.rows<<endl;
                cv::imshow("send image",left);
		cv::waitKey(1);
                imencode(".jpg",left,buff,param);
		int bufflen=buff.size();
	//	printf("size of send buff :%d\n",bufflen);
		sprintf(s,"%d",bufflen);
		send(socketfd,s,15,0);
		
	//	ofstream out("filesend.txt",ofstream::out);
		vector<char>::size_type i=0;
		for(i=0;i!=buff.size();++i)
		{
			sendline[i]=buff[i];
			
		//	out<<i<<":"<<(int)buff.at(i);
		//	out<<"\n";
		}
		//printf("the end 3 numb:%d,%d,%d\n",sendline[i-1],sendline[i-2],sendline[i-3]);
		//out.close();
		
		//将数据从uchar转换到char 后再送给send发数据是错误的，将产生数据丢失。即可，sendline为uchar型，在发送代码中转为char,如下,另外，send函数最大发送缓冲大小限制与电脑系统有关，不得超过。
		int n=send(socketfd,(const char*)(&sendline),buff.size(),0);//buff.size()==strlen(sendline)+1
//		printf("n:%d\n",n);
		if(n<=0)
		{
			printf("send fail!,the connetion may be disconnected!\n");
			break;	
		}
//		cout<<"next frame：\n";


//		break;

		//本地解码测试		
                //Mat   show= imdecode(buff,CV_LOAD_IMAGE_COLOR) ; 
		//imshow("shend image",show);
		
		//break;
		//waitKey(10);
/**
		
 		if((send(socketfd,&buff[0],buff.size(),0)) < 0)
 		{
 			printf("send mes error: %s errno : %d",strerror(errno),errno);
 			exit(0);
 		}
 		/**/
        }
 	close(socketfd);
 	printf("exit\n");
 	exit(0);
	
 }


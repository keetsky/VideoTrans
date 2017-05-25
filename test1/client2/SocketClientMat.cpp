#include "SocketMatTransmissionClient.h"

int main()
{
	SocketMatTransmissionClient socketMat;
	if (socketMat.socketConnect("192.168.1.156", 6666) < 0)
	{
		return 0;
	}
	
	cv::VideoCapture capture(0);
	cv::Mat image,left,left2;
	capture >> image;
	
	

	while (1)
	{
		if (!capture.isOpened())
			return 0;

		capture >> image;
	
		left2 = cv::Mat(image,cv::Rect(0,0,image.cols/2,image.rows));//zed相机取左边图像
                left=cv::Mat(left2,cv::Rect(0,0,640,480));
                cv::imshow("1",left);
		cv::waitKey(1);
		if (left.empty())
			return 0;

		socketMat.transmit(left);
	}

	socketMat.socketDisconnect();
	return 0;
}

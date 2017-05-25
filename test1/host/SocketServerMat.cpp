#include "SocketMatTransmissionServer.h"

int main()
{
	SocketMatTransmissionServer socketMat;
	if (socketMat.socketConnect(6666) < 0)
	{
		return 0;
	}

	cv::Mat image;
	while (1)
	{
		if(socketMat.receive(image) > 0)
		{
			cv::imshow("",image);
			cv::waitKey(1);
		}
		if(waitKey(20)==27)
                {break;}
	}

	socketMat.socketDisconnect();
	return 0;
}

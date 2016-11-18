#include<stdio.h>
#include "stopLaneDetect.h"

Mat frame;	//원 프레임
Mat edges;	//처리된 이후의 프레임
Rect Area(0, 0, 500, 320);	//관심영역

stopLaneDetect finder;

int nKey = -1;

int main(void)
{
	VideoCapture vidmat("stopLaneTest.avi");
	vidmat.set(CAP_PROP_POS_FRAMES, 200);

	while (true)
	{
		if (nKey != -1)
		{
			nKey = waitKey(0);
			nKey = -1;
		}
		else
		{
			nKey = waitKey(10);

			vidmat >> frame;

			if (frame.empty())
				break;

			finder.preprocessing(frame, edges, Area);
			stopLaneDetect realfinder;
			realfinder.transformHough(edges, frame, 0);
			imshow("output", frame);
		}
	}
	return 0;
}


#include "stopLaneDetect.h"

stopLaneDetect::stopLaneDetect()
{
}

stopLaneDetect::~stopLaneDetect()
{
}

void stopLaneDetect::intensifyWhite(cv::Mat& img, cv::Mat& out)
{
	cvtColor(img, out, COLOR_BGR2HSV);

	inRange(out, Scalar(0, 0, 170), Scalar(180, 20, 255), out); // HSV 흰색 강조

}

void stopLaneDetect::preprocessing(InputArray src, OutputArray dst, Rect Area)
{
	Mat srcmat = src.getMat();
	Mat dstmat1;
	Mat dstmat2;

	srcmat(Area).copyTo(dstmat2);	//관심영역을 복사
	intensifyWhite(dstmat2, dstmat1);
	imshow("intensifyWhite", dstmat1);

	dstmat1.copyTo(dst);
}


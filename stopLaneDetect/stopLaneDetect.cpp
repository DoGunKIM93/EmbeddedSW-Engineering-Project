#include "stopLaneDetect.h"

stopLaneDetect::stopLaneDetect()
{
}

stopLaneDetect::~stopLaneDetect()
{
}

int stopLaneDetect::calHSVAverage(cv::Mat& src)
{
	Mat srcMat;
	Mat channels[3];
	Mat temp;
	int i = 0;
	int j = 0;
	uchar* arr = NULL;

	int value = 0;
	int valueSum = 0;
	int valueAverage = 0;
	int countPixels = 0;

	src.copyTo(srcMat);

	split(srcMat, channels);
	channels[2].copyTo(temp);

	arr = temp.data;

	for (j = 0; j<temp.rows; j++) {
		for (i = 0; i<temp.cols; i++) {
			value = arr[j, i];
			valueSum = valueSum + value;
			countPixels++;
		}
	}
	valueAverage = valueSum / countPixels;
	//imshow("after calHSVAverage", temp);
	//cout << "valueAverage : " << valueAverage << endl;

	return valueAverage;
}

void stopLaneDetect::intensifyWhite(cv::Mat& img, cv::Mat& out)
{
	cvtColor(img, out, COLOR_BGR2HSV);
	int value = calHSVAverage(out);
	int V = 0;

	if (60 < value && value <= 70)
		V = 160;
	else if (70 < value && value <= 80)
		V = 165;
	else if (80 < value && value <= 90)
		V = 170;
	else if (90 < value && value <= 100)
		V = 175;
	else if (100 < value && value <= 110)
		V = 180;
	else if (110 < value && value <= 120)
		V = 185;
	else if (120 < value && value <= 130)
		V = 190;
	else if (value <= 60)
		V = 155;
	else if (value > 130)
		V = 195;

	V = V - 30;

	inRange(out, Scalar(0, 0, V), Scalar(180, 20, 255), out); // HSV 흰색 강조

}

void stopLaneDetect::preprocessing(InputArray src, OutputArray dst, Rect Area)
{
	Mat srcmat = src.getMat();
	Mat dstmat1;
	Mat dstmat2;
	Mat Cannytest;

	srcmat(Area).copyTo(dstmat2);	//관심영역을 복사
	intensifyWhite(dstmat2, dstmat1);
	imshow("intensifyWhite", dstmat1);

	GaussianBlur(dstmat1, dstmat1, Size(7, 7), 0.7, 10);
	medianBlur(dstmat1, dstmat1, 5);

	imshow("medianBlur", dstmat1);
	Canny(dstmat1, Cannytest, 30, 90); // 60 120
	imshow("Canny", Cannytest);

	Cannytest.copyTo(dst);
}


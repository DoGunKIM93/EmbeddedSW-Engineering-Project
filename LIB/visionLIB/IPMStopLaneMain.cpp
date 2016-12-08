#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "IPM.h"
#include "stoplaneDetect.h"

using namespace cv;
using namespace std;

Mat frame;
Mat edges;
Rect Area(0, 180, 640, 300);

stopLineDetect finder;

int main(int _argc, char** _argv)
{
	Mat inputImg, inputImgGray;
	Mat outputImg;

	int fd;

	//cv::VideoCapture video(0);
        VideoCapture video("/home/dogunkim/computerVision/video/redOgreenO_mix_MFC.avi");//birdView_142$


	int width = 0, height = 0, fps = 0, fourcc = 0;
	width = static_cast<int>(video.get(CV_CAP_PROP_FRAME_WIDTH));
	height = static_cast<int>(video.get(CV_CAP_PROP_FRAME_HEIGHT));
	fps = static_cast<int>(video.get(CV_CAP_PROP_FPS));
	fourcc = static_cast<int>(video.get(CV_CAP_PROP_FOURCC));

	cout << "Input video: (" << width << "x" << height << ") at " << fps << ", fourcc = " << fourcc << endl;
    
    vector<Point2f> origPoints;
    origPoints.push_back(Point2f(30, height));
    origPoints.push_back(Point2f(width-30, height));
    origPoints.push_back(Point2f(width / 2 + 100, 220));
    origPoints.push_back(Point2f(width / 2 - 120, 220));

    vector<Point2f> dstPoints;
    dstPoints.push_back(Point2f(0, height));
    dstPoints.push_back(Point2f(width, height));
    dstPoints.push_back(Point2f(width, 0));
    dstPoints.push_back(Point2f(0, 0));

	IPM ipm(Size(width, height), Size(width, height), origPoints, dstPoints);

	int frameNum = 0;
	for (; ; )
	{
		fflush(stdout);
		frameNum++;

		video >> inputImg;
		if (inputImg.empty())
			break;

		if (inputImg.channels() == 3)
			cvtColor(inputImg, inputImgGray, CV_BGR2GRAY);
		else
			inputImg.copyTo(inputImgGray);

		clock_t begin = clock();
		ipm.applyHomography(inputImg, outputImg);
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		ipm.drawPoints(origPoints, inputImg);

		imshow("Input", inputImg);
		//imshow("Output", outputImg);

        finder.preprocessing(outputImg, edges, Area);
        stopLineDetect realfinder;
        realfinder.transformHough(edges, outputImg, 0);

        imshow("final", outputImg);

		waitKey(1);
	}
	close(fd);
	return 0;
}

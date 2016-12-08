
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <ctime>
#ifdef _DEBUG
//#pragma comment(lib, "opencv_core249d.lib")
//#pragma comment(lib, "opencv_gpu249d.lib")
//#pragma comment(lib, "opencv_imgproc249d.lib")
//#pragma comment(lib, "opencv_highgui249d.lib")
#else
#pragma comment(lib, "opencv_core249.lib")
#pragma comment(lib, "opencv_gpu249.lib")
#pragma comment(lib, "opencv_imgproc249.lib")
#pragma comment(lib, "opencv_highgui249.lib")
#endif
#include "IPM.h"

using namespace cv;
using namespace std;
IPM* ipm_f1;
IPM* ipm_f;

Mat birdView_f = Mat::zeros(1000, 500, CV_8UC3);
Mat birdView_f2 = Mat::zeros(1000, 500, CV_8UC3);

int main(int _argc, char** _argv)
{
	// Images
	Mat inputImg, inputImgGray;
	Mat outputImg;

	// Video
	//cv::VideoCapture video(0);
	VideoCapture video("/home/dogunkim/computerVision/video/front_1697.avi");//birdView_142$
        video.set(CAP_PROP_POS_FRAMES, 200); //520

	// Show video information
	int width = 0, height = 0, fps = 0, fourcc = 0;
	width = static_cast<int>(video.get(CV_CAP_PROP_FRAME_WIDTH));
	height = static_cast<int>(video.get(CV_CAP_PROP_FRAME_HEIGHT));
	fps = static_cast<int>(video.get(CV_CAP_PROP_FPS));
	fourcc = static_cast<int>(video.get(CV_CAP_PROP_FOURCC));

	cout << "Input video: (" << width << "x" << height << ") at " << fps << ", fourcc = " << fourcc << endl;

	vector<Point2f> origPoints_f;
	vector<Point2f> origPoints_f1;
	vector<Point2f> origPoints_f2;

	vector<Point2f> dstPoints_f;
	vector<Point2f> dstPoints_f1;
	vector<Point2f> dstPoints_f2;

	origPoints_f.push_back(Point2f(121, 163));
	origPoints_f.push_back(Point2f(320, 158));
	origPoints_f.push_back(Point2f(320, 52)); // 320 51
	origPoints_f.push_back(Point2f(228, 84)); // 227 84

	dstPoints_f.push_back(Point2f(99, 299));
	dstPoints_f.push_back(Point2f(250, 297));
	dstPoints_f.push_back(Point2f(250, 6)); // 250 4
	dstPoints_f.push_back(Point2f(100, 148)); // 102 148

	origPoints_f1.push_back(Point2f(0, 158));
	origPoints_f1.push_back(Point2f(274, 142));
	origPoints_f1.push_back(Point2f(110, 69));
	origPoints_f1.push_back(Point2f(0, 54));

	dstPoints_f1.push_back(Point2f(250, 296));
	dstPoints_f1.push_back(Point2f(426, 300));	// 424 300
	dstPoints_f1.push_back(Point2f(424, 142));
	dstPoints_f1.push_back(Point2f(250, 18));  // 250 11

	// IPM object
	ipm_f = new IPM(Size(640, 480), Size(500, 1000), origPoints_f, dstPoints_f);
	ipm_f1 = new IPM(Size(640, 480), Size(500, 1000), origPoints_f1, dstPoints_f1);

	// Main loop
	int frameNum = 0;
	for (; ; )
	{
		printf("FRAME #%6d ", frameNum);
		fflush(stdout);
		frameNum++;

		// Get current image
		video >> inputImg;
		if (inputImg.empty())
			break;

		Mat dst_Roi1(inputImg(Rect(0, 100, 320, 320)));
		Mat dst_Roi2(inputImg(Rect(320, 100, 320, 320)));

		// Color Conversion
		if (inputImg.channels() == 3)
			cvtColor(inputImg, inputImgGray, CV_BGR2GRAY);
		else
			inputImg.copyTo(inputImgGray);

		// Process
		clock_t begin = clock();
		ipm_f->applyHomography(dst_Roi1, birdView_f);
		ipm_f1->applyHomography(dst_Roi2, birdView_f2);
		birdView_f = birdView_f + birdView_f2;

		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		printf("%.2f (ms)\r", 1000 * elapsed_secs);

		// View
		imshow("Input", inputImg);
		imshow("Output", birdView_f);
		waitKey(1);
	}

	return 0;
}

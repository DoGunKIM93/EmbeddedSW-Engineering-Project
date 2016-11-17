#pragma once
#ifndef __STOPLANE_DETECT_H__
#define __STOPLANE_DETECT_H__

#include <iostream>
#include <cstdio>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

using namespace cv;
using namespace std;

class stopLaneDetect
{
public:
	stopLaneDetect();
	~stopLaneDetect();
	// V 평균
	int calHSVAverage(cv::Mat& src);
	// 흰색 강화
	void intensifyWhite(cv::Mat& img, cv::Mat& out);
	// 전처리
	void preprocessing(InputArray src, OutputArray dst, Rect Area);
};

#endif;


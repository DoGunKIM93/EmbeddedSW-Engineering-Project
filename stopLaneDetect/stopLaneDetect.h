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
private:
	// 원 영상
	Mat img;
	// 감지한 선의 마지막 점을 포함한 벡터
	vector<Vec4i> lines;
	// 누적기 해상도 파라미터
	double deltaRho;
	double deltaTheta;
	// 선을 고려하기 전에 받아야 하는 최소 투표 개수
	int minVote;
	// 선에 대한 최소 길이
	double minLength;
	// 선에 따른 최대 허용 간격
	double maxGap;
public:
	stopLaneDetect();
	~stopLaneDetect();
	// 누적기에 해상도 설정
	void setAccResolution(double dRho, double dTheta);
	// 투표 최소 개수 설정
	void setMinVote(int minv);
	// 선 길이와 간격 설정
	void setLineLengthAndGap(double length, double gap);
	// V 평균
	int calHSVAverage(cv::Mat& src);
	// 흰색 강화
	void intensifyWhite(cv::Mat& img, cv::Mat& out);
	// 전처리
	void preprocessing(InputArray src, OutputArray dst, Rect Area);
	// 허프변환
	void transformHough(InputArray src, OutputArray original, int _input);
};

#endif;


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
#define PI 3.1415926

class stopLaneDetect
{
public:
	/////// 정지선 검출을 위한 4개의 변수
	Point selected_first_1 = Point(0,0);
	Point selected_first_2 = Point(0,0);
	Point selected_second_1 = Point(0,0);
	Point selected_second_2 = Point(0,0);

	////////////
	Point core_point = Point(0,0);
	int end = 0;
	int found = 0;

	///////// 출력 위함
	char str_buf[200];

	//////// 4개의 점 흰색 영역 비율 확인
	Mat_<uchar> find_white;
	int total_pixels = 0;
	int white_pixels = 0;

	//////// 정지선 사각형의 흰색 비율 확인을 위한 변수
	int temp_x1 = 0;
	int temp_x2 = 0;
	int temp_y1 = 0;
	int temp_y2 = 0;
	int leftest_x = 0;
	int rightest_x = 0;
	int upperest_y = 0;
	int lowerest_y = 0;

	//// Thread
	short int stop_distance = 995; // 정지선 인식 범위 후, 정지선 인식범위 내 인식 못했을 때 
	short int stop_distanceTemp = 995; // Temp 
	int detectFlag = 0;
    // 최대의 사각형 출력
	Point first;
	Point second;

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
	// 확률적 허프 변환 적용
	vector<Vec4i> findLines(Mat& binary);
	// 최대 정사각형의 점 구하기
	void findLeftestX(Point first_p1, Point frist_p2, Point second_p1, Point second_p2);
	void findRightestX(Point first_p1, Point frist_p2, Point second_p1, Point second_p2);
	void findUpperestX(Point first_p1, Point frist_p2, Point second_p1, Point second_p2);
	void findLowerestX(Point first_p1, Point frist_p2, Point second_p1, Point second_p2);
	// V 평균
	int calHSVAverage(cv::Mat& src);
	// 흰색 강화
	void intensifyWhite(cv::Mat& img, cv::Mat& out);
	// 전처리
	void preprocessing(InputArray src, OutputArray dst, Rect Area);
	// 허프변환
	void transformHough(InputArray src, OutputArray original, int _input);
	// 검출된 정지선 그리기
	void drawDetectedLanes(Mat &image, int _input);

};

#endif;


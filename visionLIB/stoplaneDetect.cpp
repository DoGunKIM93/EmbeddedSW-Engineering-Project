#include "stoplaneDetect.h"

char communication = 0;
int comflag = 0;

int i = 0;
// 기본 누적 해상도는 1각도-1화소, 간격이 없고, 최소 길이도 없음
stopLineDetect::stopLineDetect() : deltaRho(1), deltaTheta(PI / 180), minVote(10), minLength(0.), maxGap(0.){
}

stopLineDetect::~stopLineDetect()
{
}

void stopLineDetect::setAccResolution(double dRho, double dTheta) {
	deltaRho = dRho;
	deltaTheta = dTheta;
}

void stopLineDetect::setMinVote(int minv) {
	minVote = minv;
}

void stopLineDetect::setLineLengthAndGap(double length, double gap) {
	minLength = length;
	maxGap = gap;
}

vector<Vec4i> stopLineDetect::findLines(Mat& binary) {
	lines.clear();
	HoughLinesP(binary, lines, deltaRho, deltaTheta, minVote, minLength, maxGap);

	return lines;
}

unsigned short stopLineDetect::setFittingLine(long double _x) {
	y = a*pow(_x, 2) + b2*_x + c;
	y = y/10;
	y = y/2;
	return y;
}

void stopLineDetect::findLeftestX(Point first_p1, Point frist_p2, Point second_p1, Point second_p2)
{
	if (first_p1.x < frist_p2.x)
		temp_x1 = first_p1.x;
	else
		temp_x1 = frist_p2.x;

	if (second_p1.x < second_p2.x)
		temp_x2 = second_p1.x;
	else
		temp_x2 = second_p2.x;

	if (temp_x1 < temp_x2)
		leftest_x = temp_x1;
	else
		leftest_x = temp_x2;
}

void stopLineDetect::findRightestX(Point first_p1, Point frist_p2, Point second_p1, Point second_p2)
{
	if (first_p1.x > frist_p2.x)
		temp_x1 = first_p1.x;
	else
		temp_x1 = frist_p2.x;

	if (second_p1.x > second_p2.x)
		temp_x2 = second_p1.x;
	else
		temp_x2 = second_p2.x;

	if (temp_x1 > temp_x2)
		rightest_x = temp_x1;
	else
		rightest_x = temp_x2;
}

void stopLineDetect::findUpperestX(Point first_p1, Point frist_p2, Point second_p1, Point second_p2)
{
	if (first_p1.y < frist_p2.y)
		temp_y1 = first_p1.y;
	else
		temp_y1 = frist_p2.y;

	if (second_p1.y < second_p2.y)
		temp_y2 = second_p1.y;
	else
		temp_y2 = second_p2.y;

	if (temp_y1 < temp_y2)
		upperest_y = temp_y1;
	else
		upperest_y = temp_y2;
}

void stopLineDetect::findLowerestX(Point first_p1, Point frist_p2, Point second_p1, Point second_p2)
{
	if (first_p1.y > frist_p2.y)
		temp_y1 = first_p1.y;
	else
		temp_y1 = frist_p2.y;

	if (second_p1.y > second_p2.y)
		temp_y2 = second_p1.y;
	else
		temp_y2 = second_p2.y;

	if (temp_y1 > temp_y2)
		lowerest_y = temp_y1;
	else
		lowerest_y = temp_y2;
}

int stopLineDetect::calHSVAverage(cv::Mat& src)
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

void stopLineDetect::intensifyWhite(cv::Mat& img, cv::Mat& out)
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

	V = V - 50;

	inRange(out, Scalar(0, 0, V), Scalar(180, 20, 255), out); // HSV 흰색 강조
}

void stopLineDetect::preprocessing(InputArray src, OutputArray dst, Rect Area)
{
	Mat srcmat = src.getMat();
	Mat dstmat1;
	Mat dstmat2;
	Mat Cannytest;
	//int erosion_size = 5;

	srcmat(Area).copyTo(dstmat2);	//관심영역을 복사

	intensifyWhite(dstmat2, dstmat1);
	//imshow("intensifyWhite", dstmat1);

	//cvtColor(dstmat1, dstmat1, CV_BGR2GRAY);
	//Mat element = getStructuringElement(cv::MORPH_CROSS,
	//	cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
	//	cv::Point(erosion_size, erosion_size));

	//dilate(dstmat1, dstmat1, element);

	//GaussianBlur(dstmat1, dstmat1, Size(7, 7), 0.7, 10);
	//Mat kernel = Mat::ones(5, 5, CV_8UC1);
	//morphologyEx(dstmat1, dstmat1, MORPH_CLOSE, kernel1, Point(-1, 1), 5);

	medianBlur(dstmat1, dstmat1, 5);

	imshow("medianBlur", dstmat1);
	Canny(dstmat1, Cannytest, 30, 90); // 60 120
	//imshow("Canny", Cannytest);

	Cannytest.copyTo(dst);
}

void stopLineDetect::drawDetectedLines(Mat &image, int _input)
{
	core_point.x = 250;
	core_point.y = 160;

	vector<Vec4i>::const_iterator it2 = lines.begin();

	while (it2 != lines.end()) 
	{
		communication = 0;
		if (_input == 1)
		{
			if (stop_distance == 999 || stop_distance == 995)
			{
				return;
			}
		}

		Point pt1((*it2)[0], (*it2)[1]);
		Point pt2((*it2)[2], (*it2)[3]);
		//circle(image, pt1, 5, Scalar(255, 255,255), 5);
		//circle(image, pt2, 5, Scalar(255, 255, 255), 5);
		// 각도
		int test_angle = fastAtan2(pt2.x - pt1.x, pt2.y - pt1.y);
		if (((test_angle > 75) && (test_angle < 105)) || ((test_angle > -105) && (test_angle < -75)))	// 정지선 각도 판단
		{
			if (sqrt(pow(pt1.x - pt2.x, 2.0f) + pow(pt1.y - pt2.y, 2.0f)) >150.0f)
			{
				slap = ((float)pt2.y - (float)pt1.y) / ((float)pt2.x - (float)pt1.x); // 두 점을 이용한 기울기
				b = pt1.y - slap * pt1.x; // y 절편
				equation = slap * pt1.x + b; // p1을 이용한 직선의 방정식
				//line(image, pt1, pt2, Scalar(255, 0, 0), 2);

				if (selected_first_1.x == 0 && selected_first_1.y == 0 && selected_first_2.x == 0 && selected_first_2.y == 0
					&& selected_second_1.x == 0 && selected_second_1.y == 0 && selected_second_2.x == 0 && selected_second_2.y == 0)	// 첫 번째 두 개의 점 저장
				{
					if ((((slap*core_point.x) / 2) + (((-1 * core_point.y) / 2)) + b / (sqrt((slap*slap) + 1))) > -250.0f &&
						(((slap*core_point.x) / 2) + (((-1 * core_point.y) / 2)) + b / (sqrt((slap*slap) + 1))) < 250.0f)
					{
						selected_first_1 = pt1;
						selected_first_2 = pt2;
					}
				}
				else if (selected_first_1.x != 0 && selected_first_1.y != 0 && selected_first_2.x != 0 && selected_first_2.y != 0		// 두 번째 두 개의 점 저장
					&& selected_second_1.x == 0 && selected_second_1.y == 0 && selected_second_2.x == 0 && selected_second_2.y == 0)
				{
					if (fastAtan2(selected_first_2.x - selected_first_1.x, selected_first_2.y - selected_first_1.y) - fastAtan2(pt2.x - pt1.x, pt2.y - pt1.y) < 20 &&
						fastAtan2(selected_first_2.x - selected_first_1.x, selected_first_2.y - selected_first_1.y) - fastAtan2(pt2.x - pt1.x, pt2.y - pt1.y) > -20)
					{
						if (selected_first_1.y>pt1.y) // 첫 번째 두개의 y절편이 위
						{
							if (selected_first_1.y - pt1.y < 100 && selected_first_1.y - pt1.y > 20 && selected_first_2.y - pt2.y < 100 && selected_first_2.y - pt2.y > 20)
							{
								selected_second_1 = pt1;
								selected_second_2 = pt2;
								found = 1;
								y_flag = 0;
							}
						}
						else if (selected_first_1.y<pt1.y)  // 두 번째 두개의 y절편이 위
						{
							if (pt1.y - selected_first_1.y < 100 && pt1.y - selected_first_1.y > 20 && pt2.y - selected_first_2.y < 100 && pt2.y - selected_first_2.y > 20)
							{
								selected_second_1 = pt1;
								selected_second_2 = pt2;
								found = 1;
								y_flag = 1;
							}
						}
					}
				}

				if (found == 1)		// 총 4개의 점을 찾음 --> 정지선인지 판단 시작
				{
					detectFlag = 1;
					slap = ((float)selected_first_2.y - (float)selected_first_1.y) / ((float)selected_first_2.x - (float)selected_first_1.x); // 두 점을 이용한 기울기
					b = selected_first_1.y - slap * selected_first_1.x; // y 절편
					equation = slap * selected_first_1.x + b; // p1을 이용한 직선의 방정식

					if ((slap*((selected_second_1.x + selected_second_2.x) / 2)) + (-1 * ((selected_second_1.y + selected_second_2.y) / 2)) + b / (sqrt((slap*slap) + 1))>20.0f &&
						(slap*((selected_second_1.x + selected_second_2.x) / 2)) + (-1 * ((selected_second_1.y + selected_second_2.y) / 2)) + b / (sqrt((slap*slap) + 1))<100.0f)	// 2개의 점의 중점과 2개의 점의 직선 사이의 거리
					{																																					
							i++;

							findLeftestX(selected_first_1, selected_first_2, selected_second_1, selected_second_2);
							findRightestX(selected_first_1, selected_first_2, selected_second_1, selected_second_2);
							findLowerestX(selected_first_1, selected_first_2, selected_second_1, selected_second_2);
							findUpperestX(selected_first_1, selected_first_2, selected_second_1, selected_second_2);

							first.x = leftest_x;
							first.y = lowerest_y+180;

							second.x = rightest_x;
							second.y = upperest_y+180;
								

							rectangle(image, first, second, 150, 2);

							if (y_flag == 0)
								showDistance = setFittingLine(long((selected_first_1.y + selected_first_2.y) / 2));
							else if (y_flag == 1)
								showDistance = setFittingLine(long((selected_second_1.y + selected_second_2.y) / 2));

									
							if(showDistance<=5)
							{
								communication = 2;
								//comflag =1;
								printf("%d\n", communication);
							}
							else if(comflag == 0)
							{
								communication = 0;
								printf("%d\n", communication);
							}

							//printf("---%d", passValue);
							sprintf(str_buf, "Distance : %dCM", showDistance);
							//cout << showDistance << endl;
							putText(image, str_buf, Point(20, 120), FONT_HERSHEY_SIMPLEX, 1, Scalar::all(255), 1);
					}
				}
			}
		}
		++it2;
	}
}

void stopLineDetect::transformHough(InputArray src, OutputArray original, int _input)
{
	int input = _input;
	Mat srcmat = src.getMat();
	Mat originalmat = original.getMat();

	// 확률적 허프변환 파라미터 설정하기
	setLineLengthAndGap(100, 100);
	setMinVote(50);
	setAccResolution(1, PI / 180);
	
	// 선 감지
	vector<Vec4i> lines = findLines(srcmat);

	drawDetectedLines(originalmat, input);
}



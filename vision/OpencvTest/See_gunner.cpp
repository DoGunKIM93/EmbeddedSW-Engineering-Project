#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    cout << "OpenCV Version : " << CV_VERSION << std::endl;
    Mat img;
    namedWindow("EXAMPLE01", CV_WINDOW_AUTOSIZE);

    img = imread("gunners.jpg", CV_LOAD_IMAGE_COLOR);
    if (img.empty())
    {
        cout << "[!] You can NOT see the Gunners!" << std::endl;
        return -1;
    }
    imshow("EXAMPLE01", img);
    waitKey(0);
    destroyWindow("EXAMPLE01");
    return 0;
}


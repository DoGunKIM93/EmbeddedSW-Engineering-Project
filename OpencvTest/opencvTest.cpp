#include <stdio.h>
#include <math.h>
#include "cv.h"
#include "highgui.h"

int main() {

	printf("Hello Opencv\r\n");
	cvNamedWindow("opencvTest",CV_WINDOW_AUTOSIZE);
	IplImage* image=0;
	image=cvLoadImage("image.png", CV_LOAD_IMAGE_COLOR);

	if(image==0)
		printf("image doesn't exist");
	else
	{
		cvShowImage("opencvTest", image);
		cvWaitKey(0);
		cvReleaseImage(&image);
	}

	return 0;
}

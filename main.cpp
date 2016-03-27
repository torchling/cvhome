/*
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include <cvaux.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main()
{
    Mat image;// new blank image
    image = cv::imread("test.png", 1);// read the file
    namedWindow( "I want to show", CV_WINDOW_AUTOSIZE );// create a window for display.
    imshow( "I want to show", image );// show our image inside it.
    waitKey(0);// wait for a keystroke in the window
    return 0;

}

*/
#include <iostream>
#include <cv.h>
#include <highgui.h>
//
using namespace std;

int main()
{
    IplImage* img = cvLoadImage( "mp1a.jpg", -1);
    cvNamedWindow("Hello", 1);
    cvShowImage( "eg1", img );
    cvWaitKey(0);
    cvReleaseImage( &img );
    cvDestroyWindow("Hello");
    return 0;
}


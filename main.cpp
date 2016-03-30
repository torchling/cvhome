
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include <cv.h>
#include <highgui.h>

#include <vector>

using namespace std;

int histo[256]; //for histogram
int t[256];
float p=256.0;

int cnt;

int main( int argc, char **argv)
{

    IplImage *img = cvLoadImage( "mp1.jpg",1);
    IplImage *grayimg = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1 );

    IplImage *img = cvLoadImage( "mp1a.jpg",1);
    IplImage *rgb_img = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3 );

    double gray;
    CvScalar scalar1;

    p=p/(img->width*img->height);

/*--mp1---*/
    for(int i=0; i< img->height;i++)
    {
        for(int j=0; j < img->width; j++)
        {
            scalar1 = cvGet2D(img,i,j);
            for(int k=0;k<256;k++){
                if(k==scalar1.val[0])
                    histo[k]+=1;
            }
        }
    }
    t[0]=p*histo[0];
    for(int i=1; i<256; i++)
    {
        t[i]=t[i-1]+p*histo[i];
    }
    for(int i=0; i< img->height;i++)
    {
        for(int j=0; j < img->width; j++)
        {
            scalar1 = cvGet2D(img,i,j);
            for(int k=0;k<256;k++){
                if(k==scalar1.val[0])
                    cvSet2D(grayimg,i,j,cvScalar(t[k]));
            }
        }
    }

/*--mp1a---*/
    for(int i=0; i< img->height;i++)
    {
        for(int j=0; j < img->width; j++)
        {
            scalar1 = cvGet2D(img,i,j);
            for(int k=0;k<256;k++){
                if(k==scalar1.val[0])
                    histo[k]+=1;
            }
        }
    }
    t[0]=p*histo[0];
    for(int i=1; i<256; i++)
    {
        t[i]=t[i-1]+p*histo[i];
    }
    for(int i=0; i< img->height;i++)
    {
        for(int j=0; j < img->width; j++)
        {
            scalar1 = cvGet2D(img,i,j);
            for(int k=0;k<256;k++){
                if(k==scalar1.val[0])
                    cvSet2D(grayimg,i,j,cvScalar(t[k]));
            }
        }
    }

    cvNamedWindow("mp1", 1);

    cvShowImage( "mp1", grayimg );
    cvWaitKey(0);

    cvReleaseImage( &grayimg );
    cvDestroyWindow("mp1");


    return 0;
}
/*
    gray = 0.299*scalar1.val[2]
          +0.587*scalar1.val[1]
          +0.114*scalar1.val[0];
    cvSet2D(grayimg,i,j,cvScalar(gray,gray,gray));
*/


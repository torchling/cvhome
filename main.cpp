
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include <cv.h>
#include <highgui.h>

#include <vector>

using namespace std;
using namespace cv;

int histo[256]; //for histogram
int histoR[256];
int histoG[256];
int histoB[256];
int histoY[256];
int histoV[256];
int t[256];
int tR[256];
int tG[256];
int tB[256];
int tY[256];
int tV[256];
float p=256.0;
float Y,cb,cr;
int cnt;
short r,g,b;

//void equalization( int height, int width, img_before, img_after )

int main( int argc, char **argv)
{
    CvScalar scalar1;

    IplImage *img = cvLoadImage( "mp1.jpg",1);
    IplImage *grayimg = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1 );

    IplImage *src2 = cvLoadImage( "mp1a.jpg",1);
    IplImage *rgb_img = cvCreateImage(cvGetSize(src2), IPL_DEPTH_8U, 3 );

    IplImage *hsv = cvCreateImage(cvGetSize(src2), IPL_DEPTH_8U, 3);
    cvCvtColor( src2, hsv, CV_BGR2HSV );
    IplImage *hsv2 = cvCreateImage(cvGetSize(src2), IPL_DEPTH_8U, 3);

    IplImage *yuv = cvCreateImage(cvGetSize(src2), IPL_DEPTH_8U, 3 );
    cvCvtColor( src2, yuv, CV_BGR2YCrCb );
    IplImage *yuv2 = cvCreateImage(cvGetSize(src2), IPL_DEPTH_8U, 3 );

    CvSize histoSize = cvSize(256,256);

    IplImage *Image1;
    Image1 = cvCreateImage(histoSize, IPL_DEPTH_8U, 1);
    IplImage *Image2;
    Image1 = cvCreateImage(histoSize, IPL_DEPTH_8U, 1);

    IplImage *Image_rgb;
    Image1 = cvCreateImage(histoSize, IPL_DEPTH_8U, 3);
    IplImage *Image_rgb2;
    Image1 = cvCreateImage(histoSize, IPL_DEPTH_8U, 3);

    IplImage *Image_hsv;
    Image1 = cvCreateImage(histoSize, IPL_DEPTH_8U, 3);
    IplImage *Image_hsv2;
    Image1 = cvCreateImage(histoSize, IPL_DEPTH_8U, 3);

    IplImage *Image_yuv;
    Image1 = cvCreateImage(histoSize, IPL_DEPTH_8U, 3);
    IplImage *Image_yuv2;
    Image1 = cvCreateImage(histoSize, IPL_DEPTH_8U, 3);

//--mp1---
    p=256.0/(img->width*img->height);

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

//--mp1a---
    p=256.0/(src2->width*src2->height);
    //Red
    for(int i=0; i< src2->height;i++)
    {
        for(int j=0; j < src2->width; j++)
        {
            scalar1 = cvGet2D(src2,i,j);
            for(int k=0;k<256;k++){
                if(k==scalar1.val[2])
                    histoR[k]+=1;
            }
        }
    }
    tR[0]=p*histoR[0];
    for(int i=1; i<256; i++)
    {
        tR[i]=tR[i-1]+p*histoR[i];
    }
    //Green
    for(int i=0; i< src2->height;i++)
    {
        for(int j=0; j < src2->width; j++)
        {
            scalar1 = cvGet2D(src2,i,j);
            for(int k=0;k<256;k++){
                if(k==scalar1.val[1])
                    histoG[k]+=1;
            }
        }
    }
    tG[0]=p*histoG[0];
    for(int i=1; i<256; i++)
    {
        tG[i]=tG[i-1]+p*histoG[i];
    }
    //blue
    for(int i=0; i< src2->height;i++)
    {
        for(int j=0; j < src2->width; j++)
        {
            scalar1 = cvGet2D(src2,i,j);
            for(int k=0;k<256;k++){
                if(k==scalar1.val[0])
                    histoB[k]+=1;
            }
        }
    }
    tB[0]=p*histoB[0];
    for(int i=1; i<256; i++)
    {
        tB[i]=tB[i-1]+p*histoB[i];
    }
    //RGB
    for(int i=0; i< src2->height;i++)
    {
        for(int j=0; j < src2->width; j++)
        {
            scalar1 = cvGet2D(src2,i,j);
            for(int k=0;k<256;k++){
                if(k==scalar1.val[2])
                    r=tR[k];
            }
            for(int k=0;k<256;k++){
                if(k==scalar1.val[1])
                    g=tG[k];
            }
            for(int k=0;k<256;k++){
                if(k==scalar1.val[0])
                    b=tB[k];
            }
            cvSet2D(rgb_img,i,j,cvScalar(b, g, r));
        }
    }

//--mp1a_HSV---
    p=256.0/(src2->width*src2->height);

    for(int i=0; i< src2->height;i++)
    {
        for(int j=0; j < src2->width; j++)
        {
            scalar1 = cvGet2D(hsv,i,j);
            for(int k=0;k<256;k++){
                if(k==scalar1.val[2])
                    histoV[k]+=1;
            }
        }
    }
    tY[0]=p*histoY[0];
    for(int i=1; i<256; i++)
    {
        tV[i]=tV[i-1]+p*histoV[i];
    }
    for(int i=0; i< src2->height;i++)
    {
        for(int j=0; j < src2->width; j++)
        {
            scalar1 = cvGet2D(hsv,i,j);
            for(int k=0;k<256;k++){
                if(k==scalar1.val[2])
                    cvSet2D(hsv,i,j,cvScalar(scalar1.val[0],scalar1.val[1],tV[k]));
            }
        }
    }

//--mp1a_YCbCr---
    p=256.0/(src2->width*src2->height);

    for(int i=0; i< src2->height;i++)
    {
        for(int j=0; j < src2->width; j++)
        {
            scalar1 = cvGet2D(yuv,i,j);
            for(int k=0;k<256;k++){
                if(k==scalar1.val[0])
                    histoY[k]+=1;
            }
        }
    }
    tY[0]=p*histoY[0];
    for(int i=1; i<256; i++)
    {
        tY[i]=tY[i-1]+p*histoY[i];
    }
    for(int i=0; i< src2->height;i++)
    {
        for(int j=0; j < src2->width; j++)
        {
            scalar1 = cvGet2D(yuv,i,j);
            for(int k=0;k<256;k++){
                if(k==scalar1.val[0])
                    cvSet2D(yuv,i,j,cvScalar(tY[k],scalar1.val[1],scalar1.val[2]));
            }
        }
    }
    cvCvtColor( hsv, hsv2, CV_HSV2BGR );
    cvCvtColor( yuv, yuv2, CV_YCrCb2BGR );

    for(int x=0; x<256 ; x++)
    {
        for(int y=0; y<256; y++)
        {
            if((255-y)<(histo[x]/128.0))
                cvSet2D(Image1,y,x,cvScalar(0,0,0));
            else cvSet2D(Image1,y,x,cvScalar(255,255,255));
        }
    }
    for(int x=0; x<256 ; x++)
    {
        for(int y=0; y<256; y++)
        {
            if((255-y)<(histo[x]/128.0))
                cvSet2D(Image1,y,t[x],cvScalar(0,0,0));
            else cvSet2D(Image1,y,t[x],cvScalar(255,255,255));
        }
    }

    cvNamedWindow("mp1", 1);
    cvShowImage( "mp1", grayimg );

    cvNamedWindow("mp1a_RGB", 1);
    cvShowImage( "mp1a_RGB", rgb_img );

    cvNamedWindow("mp1a_HSV", 1);
    cvShowImage( "mp1a_HSV", hsv2 );

    cvNamedWindow("mp1a_YCbCr", 1);
    cvShowImage( "mp1a_YCbCr", yuv2 );

    cvNamedWindow("histo1", 1);
    cvShowImage( "histo1", Image1 );

    cvWaitKey(0);

    cvReleaseImage( &grayimg );
    cvDestroyWindow("mp1");

    cvReleaseImage( &rgb_img );
    cvDestroyWindow("mp1a_RGB");

    cvReleaseImage( &hsv );
    cvDestroyWindow("mp1a_HSV");

    cvReleaseImage( &yuv );
    cvDestroyWindow("mp1a_YCbCr");

    cvReleaseImage( &Image1 );
    cvDestroyWindow("histo1");

    return 0;
}
/*
    gray = 0.299*scalar1.val[2]
          +0.587*scalar1.val[1]
          +0.114*scalar1.val[0];
    cvSet2D(grayimg,i,j,cvScalar(gray,gray,gray));
*/


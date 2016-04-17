#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;


// Rearrange the quadrants of a Fourier image so that the origin is at
// the image center
void shiftDFT(Mat &fImage)
{
	Mat tmp, q0, q1, q2, q3;

	// first crop the image, if it has an odd number of rows or columns

	fImage = fImage(Rect(0, 0, fImage.cols & -2, fImage.rows & -2));

	int cx = fImage.cols / 2;
	int cy = fImage.rows / 2;

	// rearrange the quadrants of Fourier image
	// so that the origin is at the image center

	q0 = fImage(Rect(0, 0, cx, cy));
	q1 = fImage(Rect(cx, 0, cx, cy));
	q2 = fImage(Rect(0, cy, cx, cy));
	q3 = fImage(Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}


int main(int argc, char ** argv)
{
	const char* filename = argc >= 2 ? argv[1] : "woman.jpg";

	Mat I = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
	if (I.empty())
		return -1;

	Mat padded;                            
	//expand input image to optimal size
	int m = getOptimalDFTSize(I.rows); 
	int n = getOptimalDFTSize(I.cols);
	
	// on the border add zero values
	copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;

	merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
	dft(complexI, complexI);            // this way the result may fit in the source matrix
	
	Mat planes_mp[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) }; //planes_mp[0] is for magnitude, planes_mp[1] is for phase
	Mat recon[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };

	split(complexI, planes);            // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	

	cartToPolar(planes[0], planes[1], planes_mp[0], planes_mp[1]);
	polarToCart(planes_mp[0], planes_mp[1], recon[0], recon[1]);

	Mat recI;
	merge(recon, 2, recI);
	Mat inverseTransform;
	dft(recI, inverseTransform, DFT_INVERSE | DFT_REAL_OUTPUT);
	normalize(inverseTransform, inverseTransform, 0, 1, CV_MINMAX);
	
	imshow("Input Image", I);    // Show the result
	imshow("Reconstructed", inverseTransform);
	
	waitKey();

	return 0;
}
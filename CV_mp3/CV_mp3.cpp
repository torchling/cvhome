#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;


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
	//const char* filename1 = argc >= 2 ? argv[1] : "john.jpg";		// ½±¤¤¥¿
	//const char* filename2 = argc >= 2 ? argv[1] : "mow.jpg";		// ¤ò¿AªF
	const char* filename1 = argc >= 2 ? argv[1] : "woman.jpg";
	const char* filename2 = argc >= 2 ? argv[1] : "rectangle.jpg";


	Mat I = imread(filename1, CV_LOAD_IMAGE_GRAYSCALE);
	if (I.empty())
		return -1;

	Mat I2 = imread(filename2, CV_LOAD_IMAGE_GRAYSCALE);
	if (I.empty())
		return -1;


	/*-------------------*/

	// image 01
	Mat planes[] = { Mat_<float>(I), Mat::zeros(I.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

	dft(complexI, complexI);            // FourierTransform
	split(complexI, planes);            // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

	Mat planes_mp[] = { Mat_<float>(I), Mat::zeros(I.size(), CV_32F) }; //planes_mp[0] is for magnitude, planes_mp[1] is for phase

	cartToPolar(planes[0], planes[1], planes_mp[0], planes_mp[1]);

	/*-------------------*/

	// image 02
	Mat planes2[] = { Mat_<float>(I2), Mat::zeros(I2.size(), CV_32F) };

	merge(planes2, 2, complexI);         // Add to the expanded another plane with zeros

	dft(complexI, complexI);            // FourierTransform
	split(complexI, planes2);            // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

	Mat planes_mp2[] = { Mat_<float>(I2), Mat::zeros(I2.size(), CV_32F) }; //planes_mp[0] is for magnitude, planes_mp[1] is for phase

	cartToPolar(planes2[0], planes2[1], planes_mp2[0], planes_mp2[1]);

	/*-------------------*/

	// Creat blank Phase & magnitude
	Mat planes_blank[] = { Mat_<float>(I), Mat::zeros(I.size(), CV_32F) };

	planes_blank[0].setTo(1); //blank mag for phase
	planes_blank[1].setTo(0); //blank phase for mag

	/*-------------------*/

	Mat recon[] = { Mat_<float>(I), Mat::zeros(I.size(), CV_32F) };
	Mat recon2[] = { Mat_<float>(I2), Mat::zeros(I2.size(), CV_32F) };
	Mat recon_Phase[] = { Mat_<float>(I2), Mat::zeros(I2.size(), CV_32F) };
	Mat recon_Magnitude[] = { Mat_<float>(I2), Mat::zeros(I2.size(), CV_32F) };

	polarToCart(planes_mp2[0], planes_mp[1], recon[0], recon[1]);
	polarToCart(planes_mp[0], planes_mp2[1], recon2[0], recon2[1]);
	polarToCart(planes_blank[0], planes_mp[1], recon_Phase[0], recon_Phase[1]);
	polarToCart(planes_mp[0], planes_blank[1], recon_Magnitude[0], recon_Magnitude[1]);


	Mat recI;   merge(recon, 2, recI);
	Mat recI2;  merge(recon2, 2, recI2);
	Mat recP;   merge(recon_Phase, 2, recP);
	Mat recM;   merge(recon_Magnitude, 2, recM);

	Mat inverseTransform;
	Mat inverseTransform2;
	Mat inverseTransformP;
	Mat inverseTransformM;

	dft(recI, inverseTransform, DFT_INVERSE | DFT_REAL_OUTPUT);
	dft(recI2, inverseTransform2, DFT_INVERSE | DFT_REAL_OUTPUT);
	dft(recP, inverseTransformP, DFT_INVERSE | DFT_REAL_OUTPUT);
	dft(recM, inverseTransformM, DFT_INVERSE | DFT_REAL_OUTPUT);

	normalize(inverseTransform, inverseTransform, 0, 1, CV_MINMAX);
	normalize(inverseTransform2, inverseTransform2, 0, 1, CV_MINMAX);
	normalize(inverseTransformP, inverseTransformP, 0, 1, CV_MINMAX);
	normalize(inverseTransformM, inverseTransformM, 0, 1, CV_MINMAX);
	normalize(planes_mp[1], planes_mp[1], 0, 1, CV_MINMAX);

	shiftDFT(inverseTransformM);

	imshow("Input Image", I);
	imshow("Input Image2", I2);

	// Show the result
	imshow("Result1", inverseTransform);
	imshow("Result2", inverseTransform2);

	//
	imshow("Phase", planes_mp[1]);

	//Phase Recon
	imshow("PhaseR", inverseTransformP);
	//Magnitude Recon
	imshow("MagnitudeR", inverseTransformM);

	waitKey();

	return 0;
}
/*
Mat padded;
//expand input image to optimal size
int m = getOptimalDFTSize(I.rows);
int n = getOptimalDFTSize(I.cols);
// on the border add zero values
copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
*/
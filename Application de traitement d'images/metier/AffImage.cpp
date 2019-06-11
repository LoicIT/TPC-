#include "AffImage.h"
#include <opencv2/opencv.hpp>
# include <iostream>


using namespace cv;

AffImage::AffImage()
{
}


AffImage::~AffImage()
{
}

void AffImage::afficherImage()
{
	Mat img = imread("Image.png");
	namedWindow("image", WINDOW_NORMAL);
	imshow("image", img);
	waitKey(0);
	return 0;
}

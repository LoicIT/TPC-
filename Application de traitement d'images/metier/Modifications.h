#pragma once
#include <iostream>
#include "Controller.h"
#include "view.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>


class Modifications : public view

{
private:
	Mat Image;

public:
	Modifications();
	~Modifications();

	void LoadImage(Mat image);
void FiltreMedian(Mat image);
void FiltreGaussien(Mat image);
void GradientSobel(Mat image);
void Dilatation(Mat image);
void Erosion(Mat image);
void ContourCanny(Mat imagee);
void Seuillage(Mat image);
void Segmentation(Mat image);

virtual void notify();

void display();

};


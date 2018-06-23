#pragma once
#ifndef MYCV_H
#define MYCV_H

#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;

void MyCvtRGB2GRAY(Mat src, Mat dst);

int MyOtusThreshold(Mat src);

void MyBinary(Mat src, Mat dst, int threshold);

//void MyConvolution(Mat src, Mat dst,int para[]);

void MyHitOrMiss(Mat src, int mask[], Mat dst, int SE_ROW, int SE_COL);
void MyBinaryMorphologyErosion(Mat src, Mat dst, int para[], int SE_ROW, int SE_COL);
void MyBinaryMorphologyRough(Mat src, Mat dst, int para[], int SE_ROW, int SE_COL);

//void MyFilterGauss(Mat src, Mat dst, int size, int sigma);

//void MyEdgeSobel(Mat src, Mat dst, Mat GX, Mat GY);
//void MyEdgeCanny(Mat src, Mat dst,int high, int low, int sigma);

//void MyHoughLine(Mat src, Mat dst, int high, int low, int sigma, int MinNum);

#endif // MYCV_H


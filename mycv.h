#ifndef MYCV_H
#define MYCV_H

#include <opencv2/opencv.hpp>
using namespace cv;

void MyCvtRGB2GRAY(Mat src, Mat dst);

int MyOtusThreshold(Mat src);

void MyBinary(Mat src, Mat dst, int threshold);

void MyHitOrMiss(Mat src, int mask[], Mat dst, int SE_ROW, int SE_COL);
void MyBinaryMorphologyErosion(Mat src, Mat dst, int para[], int SE_ROW, int SE_COL);
void MyBinaryMorphologyRough(Mat src, Mat dst, int para[], int SE_ROW, int SE_COL);

#endif // MYCV_H

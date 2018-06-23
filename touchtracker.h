#pragma once
#ifndef TOUCHTRACKER_H
#define TOUCHTRACKER_H

#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <QString>
using namespace cv;

class TouchTracker
{
public:
    static int testTouch();
    static void initTouch(Mat frame);
    static void initTouch(Rect2d boxp, Mat frame);
    static bool checkTouch(Mat frame, bool verbose);

#ifdef FF_DEPRECATED
    static int example();
    static void initTouchOld(Mat frame);
    static void initTouchOld(Rect2d boxp, Mat frame);
    static void initTouchOld(Rect2d boxp, Rect2d boxs, Mat frame);
    static bool checkTouchOld(Mat frame, bool verbose = false);
#endif

private:
    TouchTracker();
    static cv::Ptr<cv::Tracker> getTracker(int type);
    static void findNib(Mat mat, int &x, int &y);
};

#endif // TOUCHTRACKER_H

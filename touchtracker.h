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
    TouchTracker();
    static int example();
private:
    static cv::Ptr<cv::Tracker> getTracker(int type);
};

#endif // TOUCHTRACKER_H

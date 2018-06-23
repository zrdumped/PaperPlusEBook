#pragma once
#ifndef IMAGECONFIG_H
#define IMAGECONFIG_H

#include <mycv.h>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <QMainWindow>
#include "QLabel"
#include "QMouseEvent"
#include "QFileDialog"
#include <qstatusbar.h>
#include <vector>
#include <thread>
#include <QTimer>
#include <QPainter>
#include <vector>
using namespace std;

enum camera {TOP, BOTTOM1, BOTTOM2};
enum calibration {NONE, RECT, PEN};

namespace Ui {
class ImageConfig;
}

class ImageConfig : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageConfig(QMainWindow *parent = 0);
    ~ImageConfig();

private:
    Ui::ImageConfig *ui;
    QLabel* rectLabel;
    QImage rectQImage;
    Mat rectMat, penMatTop;
    camera c = TOP;
    calibration clb = NONE;
    //left-up,right-up, left-down, right-down
    vector<pair<int, int>> rectPoints;
    bool choseRect = false;
    int distance = 3;
    Point penPoint;
    Rect2d roi;
    Ptr<Tracker> tracker;
    pair<double, double> lineTop;
    pair<double, double> lineBottom;
    pair<double, double> lineLeft;
    pair<double, double> lineRight;
    bool lineLeftRightParr = false;
    bool lineUpDownParr = false;
    Point verticalPoint;
    Point horizontalPoint;
    int screenHeight = 100;
    int screenWidth = 200;



    QImage ShowImage(Mat src, QLabel* label, QImage::Format format);
    void ShowImage(QPixmap src, QLabel* label);
    void ChangeButtonMode(bool openConfirm);
    void FindPointsInRect(Mat src);
    Point GetScreenPoint(Point);
    Point CallSharedPoint(pair<double, double>, pair<double, double>);
    inline double CallDistance(Point, Point);
    pair<double, double> CallLine(Point, Point);

    QTimer theTimer;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
public Q_SLOTS:
    void showCameraTop(){
        c = TOP;
    }
    void showCameraBottom1(){
        c = BOTTOM1;
    }
    void showCameraBottom2(){
        c = BOTTOM2;
    }
    void ReactangleCalibration();
    void PenCalibration();
    void updateImage();
    void confirm();
    void cancle();
    Point GetPoint();
    void test();
};

#endif // IMAGECONFIG_H

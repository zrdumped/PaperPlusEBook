#pragma once
#ifndef IMAGECONFIG_H
#define IMAGECONFIG_H

#include <mycv.h>
#include <QMainWindow>
#include "QLabel"
#include "QMouseEvent"
#include "QFileDialog"
#include <qstatusbar.h>
#include <vector>
#include <thread>
#include <QTimer>
#include <QPainter>
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
    Mat rectMat;
    camera c = TOP;
    calibration clb = NONE;
    //left-up,right-up, left-down, right-down
    vector<pair<int, int>> rectPoints;


    QImage ShowImage(Mat src, QLabel* label, QImage::Format format);
    void ShowImage(QPixmap src, QLabel* label);
    void ChangeButtonMode(bool openConfirm);
    void FindPointsInRect(Mat src, Mat dst);

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
    void updateImage();
};

#endif // IMAGECONFIG_H

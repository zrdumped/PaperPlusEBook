#include "imageconfig.h"
#include "ui_imageconfig.h"
#include <thread>
#include <iostream>
using namespace std;
using namespace cv;

extern VideoCapture capTop;
extern VideoCapture capBottom1;
extern VideoCapture capBottom2;

#define TESTING


QImage ImageConfig::ShowImage(Mat src, QLabel* label, QImage::Format format = QImage::Format_ARGB32) {
    QImage Qimg_temp = QImage((const unsigned char*)(src.data),
        src.cols, src.rows, format);
    label->setPixmap(QPixmap::fromImage(Qimg_temp));
    //label->resize(label->pixmap()->size());
    label->show();
    return Qimg_temp;
}

void ImageConfig::ShowImage(QPixmap src, QLabel* label) {
    label->setPixmap(src);
    //label->resize(label->geometry().size());
    label->show();
    return;
}


ImageConfig::ImageConfig(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageConfig)
{
    ui->setupUi(this);
    connect(&theTimer, &QTimer::timeout, this, &ImageConfig::updateImage);

    //showImage = true;

    theTimer.start(33);

    QString fileName = QFileDialog::getOpenFileName(this, NULL, NULL, "*.bmp *.jpeg *.png *.jpeg 2000 *.gif *.jpg *.mp4");
       if (fileName == NULL) return;
       rectMat = imread(fileName.toStdString());
    //capTop >> rectMat;
    cvtColor(rectMat, rectMat, CV_RGB2RGBA);
    rectLabel = ui->image;
    rectQImage = ShowImage(rectMat, rectLabel);

    //ReactangleCalibration();
    //auto func = std::bind(&ImageConfig::ShowCapture, this);
    //std::thread tmp_show_cap(&ImageConfig::ShowCapture, this);
    //tmp_show_cap.detach();
}

ImageConfig::~ImageConfig()
{
    delete ui;
}

void ImageConfig::paintEvent(QPaintEvent *event){
    ShowImage(rectMat, rectLabel);
}

void ImageConfig::updateImage(){
    switch(c){
    case TOP:
        capTop >> rectMat;
        //imshow("top camera",img);
        break;
    case BOTTOM1:
        capBottom1 >> rectMat;
        //imshow("bottom camera 1",img);
        break;
    case BOTTOM2:
        capBottom2 >> rectMat;
        //imshow("bottom camera 2",img);
        break;
    }
    cvtColor(rectMat, rectMat, CV_RGB2RGBA);
    this->update();
}


void ImageConfig::ChangeButtonMode(bool openConfirm){
    ui->pushButton->setEnabled(!openConfirm);
    ui->pushButton_2->setEnabled(!openConfirm);
    ui->pushButton_3->setEnabled(!openConfirm);
    ui->pushButton_4->setEnabled(!openConfirm);
    ui->pushButton_5->setEnabled(!openConfirm);
    ui->pushButton_6->setEnabled(!openConfirm);
    ui->pushButton_7->setEnabled(openConfirm);
    ui->pushButton_8->setEnabled(openConfirm);
}

void ImageConfig::ReactangleCalibration(){
    theTimer.stop();
    //ui->image->raise();
    clb = RECT;
#ifndef TESTING
    capTop >> rectMat;
#else
    QString fileName = QFileDialog::getOpenFileName(this, NULL, NULL, "*.bmp *.jpeg *.png *.jpeg 2000 *.gif *.jpg *.mp4");
    if (fileName == NULL) return;
    rectMat = imread(fileName.toStdString());
#endif
    cvtColor(rectMat, rectMat, CV_RGB2RGBA);

    //Mat rectSample = imread(":/images/rectSample.jpg");
    //ui->helpimage->setPixmap(QPixmap(":/images/rectSample.jpg"));
    //cvtColor(rectSample, rectSample, CV_RGB2RGBA);
    ui->helpInfoRect->raise();
    ShowImage(QPixmap(":/images/rectSample.jpg"), ui->helpimage);

    //circle(rectMat, Point(100, 100), 50, Scalar(0, 0, 255, 255), -1);
    //ShowImage(rectMat, rectLabel);
    //return;

    //rectLabel = ui->image;
    //rectQImage = ShowImage(rectMat, rectLabel);
    //QLabel* infoLabel = ui->info;
    //ui->ImageConfig->setMouseTracking(true);
    //infoLabel->setText("Start Calibration...");

    //convert from RGB to GRAY
    Mat dst = rectMat.clone();
    MyCvtRGB2GRAY(rectMat, dst);
    rectMat = dst.clone();
    //rectQImage = ShowImage(rectMat, rectLabel);

    int threshold = MyOtusThreshold(rectMat);
    cout<<threshold<<endl;
    dst = rectMat.clone();
    MyBinary(rectMat, dst, threshold);
    rectMat = dst.clone();
    //rectQImage = ShowImage(rectMat, rectLabel);

    dst = rectMat.clone();
    int para[25] =  {2, 2, 2, 2, 2,
                     2, 0, 0, 0, 2,
                     2, 0, 0, 0, 2,
                     2, 0, 0, 0, 2,
                     2, 2, 2, 2, 2};
    MyBinaryMorphologyRough(rectMat, dst, para, 2, 2);
    rectMat = dst.clone();
    //rectQImage = ShowImage(rectMat, rectLabel);

    FindPointsInRect(rectMat);
    rectQImage = ShowImage(rectMat, rectLabel);

    ui->image->setMouseTracking(true);
    //this->setMouseTracking(true);
}

void ImageConfig::PenCalibration(){
    theTimer.stop();
    ui->helpInfoPen->raise();
    clb = RECT;
    capTop >> penMatTop;

    Rect2d roi = selectROI(penMatTop, false);
    rectangle(penMatTop, roi, Scalar( 255, 0, 0 ), 2, 1 );
    destroyWindow("ROI selector");

    //Mat penMatTemp = penMatTop.clone();
    cvtColor(penMatTop, rectMat, CV_RGB2RGBA);
    //rectangle(penMatTemp, roi, Scalar( 255, 0, 0, 255 ), 2, 1 );
    //rectQImage = ShowImage(penMatTemp, rectLabel);
    Ptr<Tracker> tracker = TrackerBoosting::create();

    //Rect2d roi = selectROI(penMatTop, false);
    //imshow("Tracking", penMatTemp);
    std::cout << roi << endl;

    rectQImage = ShowImage(rectMat, ui->image);
    ui->image->clear();
    choseRect = true;
    return;
}

void ImageConfig::mouseMoveEvent(QMouseEvent *event){
//    //获得相对于图片的坐标
//    int x = event->x() - rectLabel->x();// -xoffset;
//    int y = event->y() - rectLabel->y();// -yoffset;
//                                                                                                         //超出范围不显示信息
//    if (x < 0 || x > rectLabel->width() || y < 0 || y > rectLabel->height()) {
//        statusBar()->showMessage("");
//    }
//    //显示位置和颜色信息或灰度信息
//    else {
//        QRgb rgb = rectQImage.pixel(x, y);
//        statusBar()->showMessage(QString("Pos: (%1, %2); RGB: (%3, %4, %5)").arg
//            (QString::number(x), QString::number(y)
//                , QString::number(qBlue(rgb)), QString::number(qGreen(rgb)), QString::number(qRed(rgb))));
//        /*else
//            statusBar()->showMessage(QString("Pos: (%1, %2); GRAY: %3").arg
//            (QString::number(x), QString::number(y)
//                , QString::number(qRed(rgb))));*/
//    }
}

void ImageConfig::FindPointsInRect(Mat src){
    rectPoints = {{src.rows, src.cols}, {src.rows, 0}, {0, src.cols}, {0, 0}};
    for (int i = 2; i < src.rows - 2; i++) {
        for (int j = 2; j < src.cols - 2; j++) {
            if(src.at<Vec4b>(i, j)[0])
                continue;
            cout<<i<<" "<<j<<endl;
            //left-up
            if(i <= rectPoints[0].first && j <= rectPoints[0].second){
                rectPoints[0].first = i;
                rectPoints[0].second = j;
            }
            else if(i >= rectPoints[0].first && j >= rectPoints[0].second)
                ;
            else{
                if((i * i + j * j) <
                        (rectPoints[0].first * rectPoints[0].first + rectPoints[0].second * rectPoints[0].second)){
                    rectPoints[0].first = i;
                    rectPoints[0].second = j;
                }else{
                    ;
                }
            }

            //right-up
            if(i <= rectPoints[1].first && j >= rectPoints[1].second){
                rectPoints[1].first = i;
                rectPoints[1].second = j;
            }
            else if(i >= rectPoints[1].first && j <= rectPoints[1].second)
                ;
            else{
                if((i * i + (j - src.cols) * (j - src.cols)) <
                        (rectPoints[1].first * rectPoints[1].first + (rectPoints[1].second - src.cols) * (rectPoints[1].second - src.cols))){
                    rectPoints[1].first = i;
                    rectPoints[1].second = j;
                }else{
                    ;
                }
            }

            //left-down
            if(i >= rectPoints[2].first && j <= rectPoints[2].second){
                rectPoints[2].first = i;
                rectPoints[2].second = j;
            }
            else if(i <= rectPoints[2].first && j >= rectPoints[2].second)
                ;
            else{
                if(((i - src.rows) * (i - src.rows) + j * j) <
                        ((rectPoints[2].first - src.rows) * (rectPoints[2].first - src.rows) + rectPoints[2].second * rectPoints[2].second)){
                    rectPoints[2].first = i;
                    rectPoints[2].second = j;
                }else{
                    ;
                }
            }

            //right-down
            if(i >= rectPoints[3].first && j >= rectPoints[3].second){
                rectPoints[3].first = i;
                rectPoints[3].second = j;
            }
            else if(i <= rectPoints[3].first && j <= rectPoints[3].second)
                ;
            else{
                if(((i - src.rows) * (i - src.rows) + (j - src.cols) * (j - src.cols)) <
                        ((rectPoints[3].first - src.rows) * (rectPoints[0].first - src.rows) + (rectPoints[3].second - src.cols) * (rectPoints[3].second - src.cols))){
                    rectPoints[3].first = i;
                    rectPoints[3].second = j;
                }else{
                    ;
                }
            }
        }
    }
    for(int  i = 0; i < 4; i++){
        circle(src, Point(rectPoints[i].second, rectPoints[i].first), 10, Scalar(0, 0, 255, 255), -1);
        cout<<rectPoints[i].first <<" "<<rectPoints[i].second <<endl;
    }return;
}

void ImageConfig::confirm(){
    ChangeButtonMode(false);
    ui->helpInfoDefault->raise();
}

void ImageConfig::cancle(){
    if(choseRect){
        choseRect = false;
        PenCalibration();
    }
    else{
        ChangeButtonMode(false);
        ui->helpInfoDefault->raise();
        ui->helpimage->clear();
    }
}

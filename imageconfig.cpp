#include "imageconfig.h"
#include "ui_imageconfig.h"

#include <iostream>
using namespace std;

extern VideoCapture capTop;
extern VideoCapture capBottom1;
extern VideoCapture capBottom2;

#define TESTING

ImageConfig::ImageConfig(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageConfig)
{
    ui->setupUi(this);
    ReactangleCalibration();
}

ImageConfig::~ImageConfig()
{
    delete ui;
}

QImage ImageConfig::ShowImage(Mat src, QLabel* label, QImage::Format format = QImage::Format_ARGB32) {
    QImage Qimg_temp = QImage((const unsigned char*)(src.data),
        src.cols, src.rows, format);
    label->setPixmap(QPixmap::fromImage(Qimg_temp));
    label->resize(label->pixmap()->size());
    label->show();
    return Qimg_temp;
}

void ImageConfig::ReactangleCalibration(){
#ifndef TESTING
    capTop >> rectMat;
#else
    QString fileName = QFileDialog::getOpenFileName(this, NULL, NULL, "*.bmp *.jpeg *.png *.jpeg 2000 *.gif *.jpg *.mp4");
    if (fileName == NULL) return;
    rectMat = imread(fileName.toStdString());
#endif
    cvtColor(rectMat, rectMat, CV_RGB2RGBA);

    rectLabel = ui->image;
    rectQImage = ShowImage(rectMat, rectLabel);
    //QLabel* infoLabel = ui->info;
    //infoLabel->setText("Start Calibration...");
    rectLabel->setMouseTracking(true);

    //convert from RGB to GRAY
    Mat dst = rectMat.clone();
    MyCvtRGB2GRAY(rectMat, dst);
    rectMat = dst.clone();
    rectQImage = ShowImage(rectMat, rectLabel);

    //infoLabel->setText("Start Binarization using otus algorithm...");
    int threshold = MyOtusThreshold(rectMat);
    cout<<threshold<<endl;
    dst = rectMat.clone();
    MyBinary(rectMat, dst, threshold);
    rectMat = dst.clone();
    //infoLabel->setText("Binarization using otus algorithm finished");
    //rectQImage = ShowImage(rectMat, rectLabel);

    //infoLabel->setText("Start Coarsening...");
    dst = rectMat.clone();
    int para[25] =  {2, 2, 2, 2, 2,
                     2, 0, 0, 0, 2,
                     2, 0, 0, 0, 2,
                     2, 0, 0, 0, 2,
                     2, 2, 2, 2, 2};
    MyBinaryMorphologyRough(rectMat, dst, para, 2, 2);
    //infoLabel->setText("Coarsening finished");
    rectMat = dst.clone();
    rectQImage = ShowImage(rectMat, rectLabel);
}

void ImageConfig::mouseMoveEvent(QMouseEvent *event){
    //获得相对于图片的坐标
    int x = event->x() - rectLabel->x();// -xoffset;
    int y = event->y() - rectLabel->y();// -yoffset;
                                                                                                         //超出范围不显示信息
    if (x < 0 || x > rectQImage.width() || y < 0 || y > rectQImage.height()) {
        statusBar()->showMessage("");
    }
    //显示位置和颜色信息或灰度信息
    else {
        QRgb rgb = rectQImage.pixel(x, y);
        statusBar()->showMessage(QString("Pos: (%1, %2); RGB: (%3, %4, %5)").arg
            (QString::number(x), QString::number(y)
                , QString::number(qBlue(rgb)), QString::number(qGreen(rgb)), QString::number(qRed(rgb))));
        /*else
            statusBar()->showMessage(QString("Pos: (%1, %2); GRAY: %3").arg
            (QString::number(x), QString::number(y)
                , QString::number(qRed(rgb))));*/
    }
}

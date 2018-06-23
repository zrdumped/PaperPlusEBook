#include "imageconfig.h"
#include "ui_imageconfig.h"
#include <thread>
#include <iostream>
using namespace std;
using namespace cv;

extern VideoCapture capTop;
extern VideoCapture capBottom1;
extern VideoCapture capBottom2;

//#define TESTING


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

    //QString fileName = QFileDialog::getOpenFileName(this, NULL, NULL, "*.bmp *.jpeg *.png *.jpeg 2000 *.gif *.jpg *.mp4");
      // if (fileName == NULL) return;
       //rectMat = imread(fileName.toStdString());
    capTop >> rectMat;
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

    ChangeButtonMode(true);

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

    if(rectPoints[0].first == rectPoints[1].first)
        rectPoints[1].first += 1;
    lineTop = CallLine(Point(rectPoints[0].first,rectPoints[0].second),
            Point(rectPoints[1].first,rectPoints[1].second));
    if(rectPoints[2].first == rectPoints[3].first)
        rectPoints[3].first += 1;
    lineBottom = CallLine(Point(rectPoints[2].first,rectPoints[2].second),
            Point(rectPoints[3].first,rectPoints[3].second));
    lineLeft = CallLine(Point(rectPoints[0].first,rectPoints[0].second),
            Point(rectPoints[2].first,rectPoints[2].second));
    lineRight = CallLine(Point(rectPoints[1].first,rectPoints[1].second),
            Point(rectPoints[3].first,rectPoints[3].second));
    if(lineTop.first == lineBottom.first)
        lineUpDownParr = true;
    else
        horizontalPoint = CallSharedPoint(lineTop, lineBottom);
    if(lineLeft.first == lineRight.first)
        lineLeftRightParr = true;
    else
        verticalPoint = CallSharedPoint(lineLeft, lineRight);
}

void ImageConfig::PenCalibration(){
        ChangeButtonMode(true);
    theTimer.stop();
    ui->helpInfoPen->raise();
    clb = RECT;
#ifndef TESTING
    capTop >> penMatTop;
#else
    QString fileName = QFileDialog::getOpenFileName(this, NULL, NULL, "*.bmp *.jpeg *.png *.jpeg 2000 *.gif *.jpg *.mp4");
    if (fileName == NULL) return;
    penMatTop = imread(fileName.toStdString());
#endif

    roi = selectROI(penMatTop, false);
    //rectangle(penMatTop, roi, Scalar( 255, 0, 0 ), 2, 1 );
    destroyWindow("ROI selector");

    //Mat penMatTemp = penMatTop.clone();
    cvtColor(penMatTop, rectMat, CV_RGB2RGBA);
    rectangle(rectMat, roi, Scalar( 255, 0, 0, 255 ), 2, 1 );
    //rectQImage = ShowImage(penMatTemp, rectLabel);
    tracker = TrackerBoosting::create();
    tracker->init(penMatTop, roi);

    //Rect2d roi = selectROI(penMatTop, false);
    //imshow("Tracking", penMatTemp);

    rectQImage = ShowImage(rectMat, ui->image);
    //ui->image->clear();
    choseRect = true;

    //std::cout << roi.y << roi.height << roi.x << roi.width << endl;
    //Mat target(penMatTop, Range(roi.y, roi.height), Range(roi.x, roi.width));
    Mat target = penMatTop(roi);
    Mat midI, resI;

    cvtColor(penMatTop, resI, CV_RGB2RGBA);
    MyCvtRGB2GRAY(resI, resI);
    int threshold_num = MyOtusThreshold(resI);

    cvtColor(target, target, CV_BGR2GRAY);
    Canny(target, midI, threshold_num - 20, threshold_num + 20, 3);
    imshow("canny", midI);
    //threshold(target, midI, threshold_num, 255, THRESH_BINARY);

    //resI = target.clone();
    //Canny(target, midI, threshold - 10, threshold + 10, 3);
    //imshow("canny", midI);
    //MyCvtRGB2GRAY(target, midI);
    vector<Vec4i> lines;
    HoughLinesP(midI, lines, 1, CV_PI/180, 30, 20, 5);
    //cout << midI.type() << endl;
    //HoughLinesP(midI, lines, 1, CV_PI / 360, 50);
    //MyHoughLine(midI, resI, threshold + 10, threshold - 10, 1, 50);
    vector<Vec4i>::const_iterator it = lines.begin();
    cout << lines.size() << endl;
    Mat vote_point = Mat(target.rows, target.cols, CV_32SC1, Scalar(0));
    //float fRate = (float)(CV_PI / 180);
    for (size_t i = 0; i < lines.size(); i++)
    {
//        float rho = lines[i][0], theta = lines[i][1];
//        Point pt1, pt2;
//        double a = cos(theta), b = sin(theta);
//        double x0 = a*rho, y0 = b*rho;
//        pt1.x = cvRound(x0 + 1000 * (-b));
//        pt1.y = cvRound(y0 + 1000 * (a));
//        pt2.x = cvRound(x0 - 1000 * (-b));
//        pt2.y = cvRound(y0 - 1000 * (a));
        line(target, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(255, 100, 5, 255), 2, CV_AA);

        if(lines[i][2] == lines[i][0]){
            int j = lines[i][2];
            for(int l = 0; l < target.cols; l++){
                for(int k = max(0, j - distance); k < min(target.rows, j + distance); k++){
                    vote_point.at<int>(j, l) += 1;
                }
            }
        }else{

        double k = (double)(lines[i][3] - lines[i][1]) / (double)(lines[i][2] - lines[i][0]);
        double b = lines[i][3] - k * lines[i][2];

        for(int l = 0; l < target.rows; l++){
            int j = k * l + b;
            for(int k = max(0, j - distance); k < min(target.cols, j + distance); k++){
                vote_point.at<int>(l, k) += 1;
            }
        }
        }
    }


    int max = -1;
    for (int i = 0; i < target.rows; i++) {
        for (int j = 0; j < target.cols; j++) {
            if(vote_point.at<int>(i, j) > max){
                max = vote_point.at<int>(i, j);
                penPoint = Point(i, j);
            }
        }
    }
    cout<< penPoint.x << " "<<penPoint.y << " " << max << endl;
    circle(target, penPoint, 3, Scalar(0, 0, 255, 255), -1);
    circle(rectMat, penPoint + Point(roi.x , roi.y), 3, Scalar(0, 0, 255, 255), -1);
    imshow("t", target);

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
    }
    return;
}

void ImageConfig::confirm(){
    ChangeButtonMode(false);
    ui->helpInfoDefault->raise();

    capTop >> rectMat;
    cvtColor(rectMat, rectMat, CV_RGB2RGBA);
    theTimer.start(33);
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

Point ImageConfig::CallSharedPoint(pair<double, double> l1, pair<double, double> l2){
    Point res(0, 0);
    res.x = (l2.second - l1.second) / (l1.first - l2.first);
    res.y = l1.first * res.x + l2.second;
    return res;
}

pair<double, double> ImageConfig::CallLine(Point p1, Point p2){
    double k = (double)(p1.y - p2.y) / (double)(p1.x - p2.x);
    double b = (double)p1.y - k * (double)p1.x;
    return pair<double, double>(k, b);
}

Point ImageConfig::GetScreenPoint(Point in){
    pair<double, double> lineVer, lineHor;
    Point res;
    if(lineUpDownParr){
        lineVer.first = lineTop.first;
        lineVer.second = in.y - lineVer.first * in.x;
    }else{
        lineVer = CallLine(in, verticalPoint);
    }
    Point leftSharedPoint = CallSharedPoint(lineVer, lineLeft);
    res.y = (CallDistance(leftSharedPoint, Point(rectPoints[0].first, rectPoints[0].second))
            / CallDistance( Point(rectPoints[2].first, rectPoints[2].second),  Point(rectPoints[0].first, rectPoints[0].second))) * screenHeight;

    if(lineLeftRightParr){
        lineHor.first = lineLeft.first;
        lineHor.second = in.y - lineHor.first * in.x;
    }else{
        lineHor = CallLine(in, horizontalPoint);
    }
    Point upSharedPoint = CallSharedPoint(lineVer, lineTop);
    res.x = (CallDistance(upSharedPoint,  Point(rectPoints[0].first, rectPoints[0].second))
            / CallDistance( Point(rectPoints[1].first, rectPoints[1].second),  Point(rectPoints[0].first, rectPoints[0].second))) * screenWidth;

    return res;
}

double ImageConfig::CallDistance(Point p1,  Point p2){
    double distance;
    distance = powf((p1.x - p2.x),2) + powf((p1.y - p2.y),2);
    distance = sqrtf(distance);

    return distance;
}

Point ImageConfig::GetPoint(){
    Mat temp;
    Rect2d res;
    capTop >> temp;
    double timer = (double)getTickCount();
    bool ok = tracker->update(temp, res);
    float fps = getTickFrequency() / ((double)getTickCount() - timer);
    return GetScreenPoint(Point(res.x + penPoint.x, res.y + penPoint.y));
}

void ImageConfig::test(){
    ReactangleCalibration();
    PenCalibration();
    for(int  i = 0; i < 4; i++){
        circle(rectMat, Point(rectPoints[i].second, rectPoints[i].first), 10, Scalar(0, 0, 255, 255), -1);
        cout<<rectPoints[i].first <<" "<<rectPoints[i].second <<endl;
    }
}

#pragma once
#include "mainwindow.h"
#include "touchtracker.h"
#include <QApplication>
#include <bookmetadata.h>
#include "qrcode.h"
#include <QTextCodec>
#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

VideoCapture capTop;
VideoCapture capBottom1;
VideoCapture capBottom2;

/*int testOpenCV()
{
    cv::Mat image;
    image = cv::imread("1.png");
    if(image.empty())
        return 0;
    cv::namedWindow("image show");
    cv::imshow("image show",image);
    return 0;
}
*/
int getQRcodeFromVideo(Mat img, MainWindow *main){
    static int last1=-1, last2=-1;
    imshow("img",img);

    QImage imagein = QImage((const uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888).rgbSwapped();
    int val1, val2, r=0;
    qrcode2int2(imagein, &val1, &val2, 0.5, NULL);

    if (val1 &&  last1 != val1)
        r = val1;
    else if (last2 != val2)
        r = val2;
    last1 = val1;
    last2 = val2;
      cout << "qrcode: "<<r << endl;
    main->turnToPageWithLeftPageNumber(r*2-1);
    return 0;
}


//mode = 0 none
//mode = 1 top only
//mode = 2 one bottom only
//mode = 3 two bottoms
//mode = 4 all
int initCamera(int mode, bool showImg){
    capTop = VideoCapture(1);
    Mat img;
    if(!capTop.isOpened()){
        cout<<"create camera capture error"<<endl;
        system("pause");
        exit(-1);
    }
    if(showImg){
        capTop >> img;
        imshow("top camera",img);
    }

    capBottom1 = VideoCapture(3);
    if(!capBottom1.isOpened()){
        cout<<"create camera capture error"<<endl;
        system("pause");
        exit(-1);
    }
    if(showImg){
        capBottom1 >> img;
        imshow("bottom camera 1",img);
    }

    capBottom2 = VideoCapture(2);
    if(!capBottom2.isOpened()){
        cout<<"create camera capture error"<<endl;
        system("pause");
        exit(-1);
    }
    if(showImg){
        capBottom2 >> img;
        imshow("bottom camera 2",img);
    }
    return 0;
}

void mian(MainWindow *mainwindow){
    cvvNamedWindow("img");
    // touchtracker - setup
    Mat frame;
#ifdef USE_DISK
    TouchTracker::initTouchFromDisk();
    while (video.read(frame)) {
        int key = waitKey(1);
        if (key == 27)
            break;
        Rect2d boxp = getRectFromDisk();
        rectangle(frame, boxp, Scalar( 255, 0, 0 ), 2, 1 );
        imshow("Touch Tracking", frame);
    }
#else
    while (capBottom1.read(frame)) {
        //resize(frame, frame, Size(320, 240), 0, 0);
        int key = waitKey(1);
        if (key == 27)
            break;
        imshow("Touch Tracking", frame);
    }
    TouchTracker::initTouchIntoDisk(frame);
#endif
    cout << "enter loop" << endl;
    bool verbose = true, faker = false;
    while (1) {
        capBottom1.read(frame);
        int key = waitKey(1);
        if(key == 27)
            break;
        else if (key == 'd')
            verbose = !verbose;
        else if (key == 'f') {
            TouchTracker::initTouchIntoDisk(frame);
            continue;
        }
        else if (key == 's') {
            faker = !faker;
        }

        // touch tracker
        Mat topImage;
        capTop >> topImage;
        bool touching = TouchTracker::checkTouch(frame, verbose);
      //  cout << "tt complete." << endl;
        imshow("Touch bottom", frame);
        // qrcode
       // capTop.read(frame);
        getQRcodeFromVideo(topImage, mainwindow);
       // cout << "qr complete." << endl;
        // pen tracker
        Point penPoint = mainwindow->window->GetPoint(touching, topImage);
        if (touching) {
            putText(frame, "Touching", Point(50,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
            //draw
           // std::cout<<"penpoint x: "<<penPoint.x<<"penpoint y: "<<penPoint.y<<std::endl;
            mainwindow->simulateClick(penPoint.x, penPoint.y);
        }
        else{
            mainwindow->simulateFly();
        }
        //cout << "pen complete" << endl;
        imshow("Touch top", topImage);
    }
    destroyWindow("Touch Tracking");

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //testOpenCV();
    initCamera(4,false);
    //getQRcodeFromVideo(&w);
    mian(&w);
    //TouchTracker::testTouchPlus();
    return a.exec();
}

#pragma once
#include "mainwindow.h"
#include <QApplication>
#include <bookmetadata.h>
//#include "qrcode.h"
#include <opencv2/opencv.hpp>
#include <iostream>
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

int getQRcodeFromVideo(){
    VideoCapture cap(3);
    if(!cap.isOpened()){
        cout<<"create camera capture error"<<endl;
        system("pause");
        exit(-1);
    }
    cvNamedWindow("img");
    Mat img;
    while(1)
    {
        cap >> img;
        imshow("img",img);

        int r = qrcode2int(QImage((const uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888).rgbSwapped(), NULL );
        char c = cvWaitKey(33);
        if(c == 'a') break;
        cout << r<< endl;
    }
    return 0;
}
*/

//mode = 0 none
//mode = 1 top only
//mode = 2 one bottom only
//mode = 3 two bottoms
//mode = 4 all
int initCamera(int mode, bool showImg){
    switch(mode){
    case 1:
        capTop = VideoCapture(2);
        if(!capTop.isOpened()){
            cout<<"create camera capture error"<<endl;
            system("pause");
            exit(-1);
        }
        if(showImg){
            Mat img;
            capTop >> img;
            imshow("top camera",img);
        }
        break;
    default:
        break;
    }
    return 0;
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //testOpenCV();
    //getQRcodeFromVideo();
    initCamera(1,false);
    return a.exec();
}

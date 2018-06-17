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
    capTop = VideoCapture(2);
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

    capBottom1 = VideoCapture(2);
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

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //testOpenCV();
    //getQRcodeFromVideo();
    initCamera(4,false);
    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>

#include <opencv2/opencv.hpp>
#include <iostream>

int testOpenCV()
{
    cv::Mat image;
    image = cv::imread("1.png");
    if(image.empty())
        return 0;
    cv::namedWindow("image show");
    cv::imshow("image show",image);
    return 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //testOpenCV();

    return a.exec();
}

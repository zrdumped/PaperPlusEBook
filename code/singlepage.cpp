#include "singlepage.h"
#include "ui_singlepage.h"
#include <iostream>
#include <QMouseEvent>
#include <opencv2/opencv.hpp>
SinglePage::SinglePage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SinglePage)
{
    ui->setupUi(this);
    note = new QLabel(this);
    note->setAttribute(Qt::WA_TranslucentBackground);
    thisPoint = lastPoint = QPoint(-1,-1);
}

SinglePage::~SinglePage()
{
    delete ui;
}

void SinglePage::setContent(QString content, int pageIndex, int totalPageNum){
    ui->content->setText(content);
    if(totalPageNum > 0){
        ui->pageNumber->setText(tr("%1 / %2").arg(QString::number(pageIndex + 1), QString::number(totalPageNum)));
        totalPageNumber = totalPageNum;
    }
    else
        ui->pageNumber->setText(tr("%1 / %2").arg(QString::number(pageIndex + 1), QString::number(totalPageNumber)));
}

void SinglePage::setTotalPageNumber(int totalPageNum){
    totalPageNumber = totalPageNum;
}

void SinglePage::setPageNumberEmpty(){
    ui->pageNumber->setText("");
}

void SinglePage::setNote(QImage img){
    QPixmap pixmap = QPixmap(QSize(ui->content->width(),ui->content->height()));
    if(img.isNull()){
        //pixmap.fill(Qt::white);
        pixmap.fill(Qt::transparent);
    }
    else{
        pixmap = QPixmap::fromImage(img);
        pixmap = pixmap.scaled(ui->content->width(),ui->content->height());
    }
    note->setGeometry(0, 0, ui->content->width(),ui->content->height());
    note->setPixmap(pixmap);
    noteImage = note->pixmap()->toImage();
}

QImage SinglePage::getNote(){
    if(note->pixmap() && !note->pixmap()->isNull())
        return QImage(note->pixmap()->toImage());
    return QImage();
}

void SinglePage::clearNote(){
    note->setPixmap(QPixmap());
}

void SinglePage::setPainter(QColor color, int width){
    painterColor = color;
    painterWidth = width;
    std::cout<<"width: "<<width<<std::endl;
}

void SinglePage::cleanDotHistory(){
    thisPoint = lastPoint = QPoint(-1,-1);

}

void SinglePage::mousePressEvent(QMouseEvent *event){
    int x = event->pos().x();
    int y =event->pos().y();
    lastPoint = thisPoint;
    thisPoint = QPoint(x, y);
     int xend = noteImage.width();
    xend = (xend > x + painterWidth)?x + painterWidth : xend;
    int yend = noteImage.height();
    yend = (yend > y + painterWidth)?y + painterWidth : yend;
     cv::Mat mat = cv::Mat(noteImage.height(), noteImage.width(),CV_8UC4, (void*)noteImage.constBits(), noteImage.bytesPerLine());
    if(lastPoint.x() < 0){
        cv::circle(mat, cv::Point(thisPoint.x(), thisPoint.y()), painterWidth, cv::Scalar(painterColor.red(), painterColor.green(), painterColor.blue(), painterColor.alpha()), -1);
    }
    else{
         cv::line(mat, cv::Point(lastPoint.x(), lastPoint.y()), cv::Point(thisPoint.x(), thisPoint.y()), cv::Scalar(painterColor.red(), painterColor.green(), painterColor.blue(), painterColor.alpha()), painterWidth, CV_AA);
    }
     const uchar *pSrc = (const uchar*)mat.data;
    noteImage = QImage(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32).copy();
    //mat = cv::Mat(noteImage.height(), noteImage.width(), CV_8UC4, noteImage.bits());
    //std::cout<<"matok"<<mat.rows<<" "<<mat.cols<<std::endl;

    note->setPixmap(QPixmap::fromImage(noteImage));
    std::cout<<"setok"<<std::endl;
}

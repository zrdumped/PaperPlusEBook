#include "singlepage.h"
#include "ui_singlepage.h"
#include <iostream>
#include <QMouseEvent>
SinglePage::SinglePage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SinglePage)
{
    ui->setupUi(this);
    note = new QLabel(this);
    note->setAttribute(Qt::WA_TranslucentBackground);
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
}

void SinglePage::mousePressEvent(QMouseEvent *event){
    int x = QCursor::pos().x();
    int y = QCursor::pos().y();
    int xend = noteImage.width();
    xend = (xend > x + painterWidth)?x + painterWidth : xend;
    int yend = noteImage.height();
    yend = (yend > y + painterWidth)?y + painterWidth : yend;
    for(int i = x; i < xend; i ++){
        for(int j = y; j < yend; j ++){
            noteImage.setPixelColor(note->mapFromGlobal(QPoint(i, j)), painterColor);
        }
    }
    note->setPixmap(QPixmap::fromImage(noteImage));
}

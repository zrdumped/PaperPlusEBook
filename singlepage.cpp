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

void SinglePage::mousePressEvent(QMouseEvent *event){
    noteImage.setPixelColor(note->mapFromGlobal(event->pos()), Qt::red);
    note->setPixmap(QPixmap::fromImage(noteImage));
}

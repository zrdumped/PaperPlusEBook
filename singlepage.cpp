#include "singlepage.h"
#include "ui_singlepage.h"

SinglePage::SinglePage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SinglePage)
{
    ui->setupUi(this);
}

SinglePage::~SinglePage()
{
    delete ui;
}

void SinglePage::setContent(QString content, int pageNumber, int totalPageNum){
    ui->content->setText(content);
    if(totalPageNum > 0){
        ui->pageNumber->setText(tr("%1 / %2").arg(QString::number(pageNumber), QString::number(totalPageNum)));
        totalPageNumber = totalPageNum;
    }
    else
        ui->pageNumber->setText(tr("%1 / %2").arg(QString::number(pageNumber), QString::number(totalPageNumber)));
}

void SinglePage::setTotalPageNumber(int totalPageNum){
    totalPageNumber = totalPageNum;
}

void SinglePage::setPageNumberEmpty(){
    ui->pageNumber->setText("");
}

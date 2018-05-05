#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "qrcode.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //testQRCode(ui->label);
    //generateQRCodes(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::normalWarning(QString msg){
    QMessageBox msgBox(QMessageBox::Warning, tr("警告"), msg, 0, this);
    msgBox.addButton(tr("确认"), QMessageBox::AcceptRole);
    msgBox.setModal(false);
    msgBox.exec();
}

void MainWindow::normalInformation(QString msg){
    QMessageBox msgBox(QMessageBox::Information, tr("提示"), msg, 0, this);
    msgBox.addButton(tr("确认"), QMessageBox::AcceptRole);
    msgBox.setModal(false);
    msgBox.exec();
}

bool MainWindow::normalDecision(QString msg){
    QMessageBox msgBox(QMessageBox::Information, tr("提示"), msg, 0, this);
    msgBox.addButton(tr("确认"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("取消"), QMessageBox::RejectRole);
    msgBox.setModal(false);
    if(msgBox.exec() == QMessageBox::AcceptRole){
        return true;
    }
    else{
        return false;
    }
}

int MainWindow::InitPageNumber(){
    //check qrcode and records

    //no records, set page number with the qrcode
    //0 for now
    return 0;
}

int MainWindow::SetPage(){
    /*QImage leftpgimg = NULL, rightpgimg = NULL;
    int maxpgs = book->numPages();
    if(left_page_num + 1 <= 0){
        //todo: nothing for now, might be default image, but has to be done
    }
    else if(left_page_num <= 0){
        //the first page is on the right
        rightpgimg = book->page(left_page_num + 1)->renderToImage(pg_width, pg_height);
        ui->LeftPG->setPixmap(QPixmap::fromImage(rightpgimg));
        //todo: deal with left

    }
    else if(left_page_num >= maxpgs){
        //todo: nothing for now, might be default image, but has to be done
    }
    else if(left_page_num + 1 >= maxpgs){
        //the last page is on the left
        leftpgimg = book->page(left_page_num)->renderToImage(pg_width, pg_height);
        ui->LeftPG->setPixmap(QPixmap::fromImage(leftpgimg));
        //todo: deal with right

    }
    else{
        //normal pages
        leftpgimg = book->page(left_page_num)->renderToImage(pg_width, pg_height);
        rightpgimg = book->page(left_page_num + 1)->renderToImage(pg_width, pg_height);
        ui->LeftPG->setPixmap(QPixmap::fromImage(leftpgimg));
        ui->RightPG->setPixmap(QPixmap::fromImage(rightpgimg));
    }*/
    return left_page_num;
}

void MainWindow::SelectBook(){
    //choose a book
    book_name = QFileDialog::getOpenFileName(this, NULL, NULL, "*.pdf");
    if (book_name == NULL)
        return;
    //set up document
    //book = Poppler::Document::load(book_name);
    //set page number
    left_page_num = InitPageNumber();
    //set up page image
    SetPage();
    if(left_page_num < 0)
        normalWarning("无可读内容");
    return;

}

int MainWindow::turnover(int pages){
    left_page_num += pages;
    //reset page images
    SetPage();
    return left_page_num;
}

int MainWindow::AddPageNumber(int number){
    //adjust offset
    int n = base_offset;
    int off = number - base_offset;
    if(left_page_num + off < 0)
        base_offset = 0;
   /* else if(left_page_num + off + 1 > book->numPages())
        base_offset = book->numPages() - 2;*/
    else{
        base_offset += number;
    }
    //change page and the offset label in ui
    ui->Offset->setText(QString::number(turnover(base_offset - n)));
    return base_offset;
}

void MainWindow::SetOffset(){
    //add quantity of book pages for now
    AddPageNumber(book_page_num);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "qrcode.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
//#include <poppler/cpp/poppler-image.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Offset->setText(QString::number(0));
    //testQRCode(ui->label);
    //generateQRCodes(100);
    ui->LeftPG->setPixmap(QPixmap(":/icons/books.png"));
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
    book.seekg(left_page_num * each_page_bytes, std::ios::beg);
    char buf[12];
    book.read(buf, each_page_bytes);
    buf[each_page_bytes] = '\0';
    ui->LeftPG->setText(QString::fromLocal8Bit(buf, each_page_bytes));
    std::cout<<buf<<std::endl;
    book.read(buf, each_page_bytes);
    ui->RightPG->setText(QString::fromLocal8Bit(buf, each_page_bytes));
    /*QImage leftpgimg, rightpgimg;
    int maxpgs = book->numPages();
    if(left_page_num + 1 < 0 || left_page_num >= maxpgs){
        //white
        leftpgimg = QImage(pg_width, pg_height, QImage::Format_RGBA8888);
        leftpgimg.fill(QColor(255,255,255));
        ui->LeftPG->setPixmap(QPixmap::fromImage(leftpgimg));
        rightpgimg = QImage(pg_width, pg_height, QImage::Format_RGBA8888);
        rightpgimg.fill(QColor(255,255,255));
        ui->RightPG->setPixmap(QPixmap::fromImage(rightpgimg));
    }
    else if(left_page_num < 0){
        Poppler::Page *rightpg = book->page(0);
        //the first page is on the right
        rightpgimg = rightpg->renderToImage(res_x, res_y);
        rightpgimg = rightpgimg.scaled(pg_width, pg_height);
        ui->RightPG->setPixmap(QPixmap::fromImage(rightpgimg));
        //deal with left
        leftpgimg = QImage(leftpgimg.width(), leftpgimg.height(), QImage::Format_RGBA8888);
        leftpgimg.fill(QColor(255,255,255));
        ui->LeftPG->setPixmap(QPixmap::fromImage(leftpgimg));
        delete rightpg;
    }
    else if(left_page_num + 1 >= maxpgs){
        Poppler::Page *leftpg = book->page(maxpgs - 1);
        //the last page is on the left
        leftpgimg = leftpg->renderToImage(res_x, res_y);
        leftpgimg = leftpgimg.scaled(pg_width,pg_height);
        ui->LeftPG->setPixmap(QPixmap::fromImage(leftpgimg));
        //deal with right
        rightpgimg = QImage(leftpgimg.width(), leftpgimg.height(), QImage::Format_RGBA8888);
        rightpgimg.fill(QColor(255,255,255));
        ui->RightPG->setPixmap(QPixmap::fromImage(rightpgimg));
        delete leftpg;
    }
    else{
        //normal pages
        Poppler::Page *leftpg = book->page(left_page_num);
        Poppler::Page *rightpg = book->page(left_page_num + 1);
        leftpgimg = leftpg->renderToImage(res_x, res_y,-1,-1,leftpg->pageSize().width(),leftpg->pageSize().height());
        rightpgimg = rightpg->renderToImage(res_x, res_y,-1,-1,rightpg->pageSize().width(),rightpg->pageSize().height());
        leftpgimg = leftpgimg.scaled(pg_width, pg_height);
        rightpgimg = rightpgimg.scaled(pg_width, pg_height);
        std::cout<<leftpgimg.size().height()<<" "<<rightpgimg.size().width()<<std::endl;
        ui->LeftPG->setPixmap(QPixmap::fromImage(leftpgimg));
        ui->RightPG->setPixmap(QPixmap::fromImage(rightpgimg));
        delete leftpg;
        delete rightpg;
    }*/
    return left_page_num;
}

void MainWindow::SelectBook(){
    //choose a book
    book_name = QFileDialog::getOpenFileName(this, NULL, NULL, "*.txt");
    if (book_name == NULL)
        return;
    //set up document
   // book = Poppler::Document::load(book_name);
    book.open(book_name.toLocal8Bit().toStdString());

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
    book.seekg(0, book.end);
    size_t p = book.tellg();
    if(p%each_page_bytes)
        p = p/each_page_bytes + 1;
    else
        p = p/each_page_bytes;

    int n = base_offset;
        int off = number + base_offset;
        if(left_page_num + off < 0)
            base_offset = 0;
        else if(left_page_num + off + 1 > p)
            base_offset = (p - 2)>0?p-2:0;
        else{
            base_offset += number;
        }
    //adjust offset
   /* int n = base_offset;
    int off = number + base_offset;
    if(left_page_num + off < 0)
        base_offset = 0;
//    else if(left_page_num + off + 1 > book->numPages())
//        base_offset = book->numPages() - 2;
    else{
        base_offset += number;
    }*/
    //change page and the offset label in ui
    ui->Offset->setText(QString::number(turnover(base_offset - n)));
    return base_offset;
}

void MainWindow::SetOffset(){
    /*if(!book)
        return;
    //add quantity of book pages for now*/
    AddPageNumber(book_page_num);
}

void MainWindow::SetOffsetTmp(){
    /*if(!book)
        return;
    //minus quantity of book pages for now*/
    AddPageNumber(-book_page_num);
}

void MainWindow::OpenImageConfigureWindow(){
    window = new ImageConfig(this);
    window->show();
}

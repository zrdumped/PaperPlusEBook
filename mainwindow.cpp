#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "qrcode.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QLayout>
//#include <poppler/cpp/poppler-image.h>
/*
 * Menu: QPushButton{background-color: rgb(179, 208, 255); border-radius: 20px;  border: 1px rgb(179, 208, 255);} minimum height: 40px
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //set QZxing side lengths
    ui->leftQZxing->setMinimumWidth(qzxingSideLength);
    ui->rightQZxing->setMinimumWidth(qzxingSideLength);
    ui->leftQZxing->setMinimumHeight(qzxingSideLength);
    ui->rightQZxing->setMinimumHeight(qzxingSideLength);
    ui->leftQZxing->setMaximumWidth(qzxingSideLength);
    ui->rightQZxing->setMaximumWidth(qzxingSideLength);
    ui->leftQZxing->setMaximumHeight(qzxingSideLength);
    ui->rightQZxing->setMaximumHeight(qzxingSideLength);
    //set Paddings
    ui->leftPadding->setMinimumWidth(sidePaddingWidth);
    ui->rightPadding->setMinimumWidth(sidePaddingWidth);
    ui->middleUpPadding->setMinimumWidth(middlePaddingWidth);
    ui->middlePadding->setMinimumWidth(middlePaddingWidth);
    ui->middlePadding->setMaximumWidth(middlePaddingWidth);
    ui->leftPadding->setMaximumWidth(sidePaddingWidth);
    ui->rightPadding->setMaximumWidth(sidePaddingWidth);
    ui->middleUpPadding->setMaximumWidth(middlePaddingWidth);
    //set UI icons and hide
    //imageConfigure
    QIcon icon = ui->imageConfigure->icon();
    ui->imageConfigure->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/imageConfigure.png"), QIcon::Normal);
    ui->imageConfigure->setIcon(icon);
    ui->imageConfigure->setHidden(true);
    //book selector
    icon = ui->bookSelector->icon();
    ui->bookSelector->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/books.png"), QIcon::Normal);
    ui->bookSelector->setIcon(icon);
    ui->bookSelector->setHidden(true);
    //note selector
    icon = ui->noteSelector->icon();
    ui->noteSelector->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/notes.png"), QIcon::Normal);
    ui->noteSelector->setIcon(icon);
    ui->noteSelector->setHidden(true);
    //pen
    icon = ui->penUI->icon();
    ui->penUI->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/pencil.png"), QIcon::Normal);
    icon.addPixmap(QPixmap(":/icons/pencilSelected.png"), QIcon::Selected);
    ui->penUI->setIcon(icon);
    ui->penUI->setHidden(true);
    //eraser
    icon = ui->eraserUI->icon();
    ui->eraserUI->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/eraser.png"), QIcon::Normal);
    icon.addPixmap(QPixmap(":/icons/eraserSelected.png"), QIcon::Selected);
    ui->eraserUI->setIcon(icon);
    ui->eraserUI->setHidden(true);
    //page offset setter
    icon = ui->pageOffsetSetter->icon();
    ui->pageOffsetSetter->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/offset.png"), QIcon::Normal);
    ui->pageOffsetSetter->setIcon(icon);
    ui->pageOffsetSetter->setHidden(true);
    //day or night
    icon = ui->dayOrNight->icon();
    ui->dayOrNight->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/moon.png"), QIcon::Selected);
    icon.addPixmap(QPixmap(":/icons/sun.png"), QIcon::Normal);
    ui->dayOrNight->setIcon(icon);
    ui->dayOrNight->setHidden(true);
    //hide bookname
    ui->bookName->setHidden(true);
    ui->bookName->setMinimumWidth(200);
    //testQRCode(ui->label);
    //generateQRCodes(100);
    //for now, for debug...
    showAllUIs();
    //bookMenu
    bookMenu = new Menu(this, 8);
    bookMenu->setHidden(true);
    //noteMenu
    noteMenu = new Menu(this, 8);
    noteMenu->setHidden(true);
    //penStyle
    penStyle = new ArrowWidget(this);
    penStyle->setHidden(true);
    //choosebookpage
    choosebookpage = new ChooseBookPage(this);
    choosebookpage->setHidden(true);
    //choosenotepage
    choosenotepage = new ChooseNotePage(this);
    //choosenotepage->setHidden(true);
    //setup page layout
    ui->leftPage->setLayout(new QHBoxLayout());
    ui->rightPage->setLayout(new QHBoxLayout());
    QLayout *leftPGLayout = ui->leftPage->layout();
    leftPGLayout->setMargin(0);
    leftPGLayout->addWidget(choosebookpage);
    leftPGLayout->addWidget(choosenotepage);
    QLayout *rightPGLayout = ui->rightPage->layout();
    rightPGLayout->setMargin(0);
    //rightPGLayout->addWidget(choosebookpage);
    //ui->leftPage->setLayout(leftPGLayout);
    //eraserStyle
    //eraserStyle = new ArrowWidget(this);
    //offsetSetter
    //offsetSetter = new ArrowWidget(this);
    //set daymode Lighting
    changeLightingMode();
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
    /*book.seekg(left_page_num * each_page_bytes, std::ios::beg);
    char buf[12];
    book.read(buf, each_page_bytes);
    buf[each_page_bytes] = '\0';
    ui->LeftPG->setText(QString::fromLocal8Bit(buf, each_page_bytes));
    std::cout<<buf<<std::endl;
    book.read(buf, each_page_bytes);
    ui->RightPG->setText(QString::fromLocal8Bit(buf, each_page_bytes));
    QImage leftpgimg, rightpgimg;
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
    /*//choose a book
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
    return;*/

}

int MainWindow::turnover(int pages){
    /*left_page_num += pages;
    //reset page images
    SetPage();
    return left_page_num;*/
}

int MainWindow::AddPageNumber(int number){
    /*book.seekg(0, book.end);
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
    int n = base_offset;
    int off = number + base_offset;
    if(left_page_num + off < 0)
        base_offset = 0;
//    else if(left_page_num + off + 1 > book->numPages())
//        base_offset = book->numPages() - 2;
    else{
        base_offset += number;
    }
    //change page and the offset label in ui
    ui->Offset->setText(QString::number(turnover(base_offset - n)));
    return base_offset;
    */
}

void MainWindow::SetOffset(){
    /*if(!book)
        return;
    //add quantity of book pages for now
    AddPageNumber(book_page_num);*/
}

void MainWindow::SetOffsetTmp(){
    /*if(!book)
        return;
    //minus quantity of book pages for now
    AddPageNumber(-book_page_num);*/
}

void MainWindow::OpenImageConfigureWindow(){
    window = new ImageConfig(this);
    window->show();
}

void MainWindow::showAllUIs(){
    ui->bookName->setHidden(false);
    ui->dayOrNight->setHidden(false);
    ui->bookSelector->setHidden(false);
    ui->noteSelector->setHidden(false);
    ui->eraserUI->setHidden(false);
    ui->penUI->setHidden(false);
    ui->pageOffsetSetter->setHidden(false);
    ui->imageConfigure->setHidden(false);
}

void MainWindow::hideAllUIs(){
    ui->bookName->setHidden(true);
    ui->dayOrNight->setHidden(true);
    ui->bookSelector->setHidden(true);
    ui->noteSelector->setHidden(true);
    ui->eraserUI->setHidden(true);
    ui->penUI->setHidden(true);
    ui->pageOffsetSetter->setHidden(true);
    ui->imageConfigure->setHidden(true);
}

void MainWindow::changeLightingMode(){
    isDayLighting = !isDayLighting;
    if(isDayLighting){
        ui->leftPage->setStyleSheet(dayLightStyle);
        ui->rightPage->setStyleSheet(dayLightStyle);
        ui->leftUIBar->setStyleSheet(dayLightStyle);
        ui->rightUIBar->setStyleSheet(dayLightStyle);
        ui->bookName->setStyleSheet(dayLightStyle);
    }
    else{
        ui->leftPage->setStyleSheet(nightLightStyle);
        ui->rightPage->setStyleSheet(nightLightStyle);
        ui->leftUIBar->setStyleSheet(nightLightStyle);
        ui->rightUIBar->setStyleSheet(nightLightStyle);
        ui->bookName->setStyleSheet(nightLightStyle);
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qrcode.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    testQRCode(ui->label);
    generateQRCodes(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "imageconfig.h"
#include "ui_imageconfig.h"

ImageConfig::ImageConfig(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageConfig)
{
    ui->setupUi(this);
}

ImageConfig::~ImageConfig()
{
    delete ui;
}

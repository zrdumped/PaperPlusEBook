#include "imageconfig.h"
#include "ui_imageconfig.h"

ImageConfig::ImageConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageConfig)
{
    ui->setupUi(this);
}

ImageConfig::~ImageConfig()
{
    delete ui;
}

#include "emptynote.h"
#include "ui_emptynote.h"

EmptyNote::EmptyNote(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::EmptyNote)
{
    ui->setupUi(this);
}

EmptyNote::~EmptyNote()
{
    delete ui;
}

#include "emptybook.h"
#include "ui_emptybook.h"

EmptyBook::EmptyBook(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::EmptyBook)
{
    ui->setupUi(this);
}

EmptyBook::~EmptyBook()
{
    delete ui;
}

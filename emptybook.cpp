#include "emptybook.h"
#include "ui_emptybook.h"

EmptyBook::EmptyBook(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::EmptyBook)
{
    ui->setupUi(this);
    QIcon icon = ui->addBook->icon();
    icon.addPixmap(QPixmap(":/icons/plus.png"), QIcon::Normal);
    ui->addBook->setIcon(icon);
}

EmptyBook::~EmptyBook()
{
    delete ui;
}

QPushButton *EmptyBook::addBookBtn(){
    return ui->addBook;
}

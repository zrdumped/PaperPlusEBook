#include "choosebookpage.h"
#include "ui_choosebookpage.h"

ChooseBookPage::ChooseBookPage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ChooseBookPage)
{
    ui->setupUi(this);
    QIcon icon = ui->addBook->icon();
    icon.addPixmap(QPixmap(":/icons/plus.png"), QIcon::Normal);
    ui->addBook->setIcon(icon);
    ui->booksLabel->setPixmap(QPixmap(":/icons/booksLabel.png"));
}

ChooseBookPage::~ChooseBookPage()
{
    delete ui;
}

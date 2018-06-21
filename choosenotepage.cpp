#include "choosenotepage.h"
#include "ui_choosenotepage.h"
#include <QIcon>

ChooseNotePage::ChooseNotePage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ChooseNotePage)
{
    ui->setupUi(this);
    QIcon icon = ui->addNote->icon();
    icon.addPixmap(QPixmap(":/icons/plus.png"), QIcon::Normal);
    ui->addNote->setIcon(icon);
    ui->notesLabel->setPixmap(QPixmap(":/icons/notesLabel.png"));
    icon = ui->backToBookChoose->icon();
    icon.addPixmap(QPixmap(":/icons/return.png"), QIcon::Normal);
    ui->backToBookChoose->setIcon(icon);
}

ChooseNotePage::~ChooseNotePage()
{
    delete ui;
}

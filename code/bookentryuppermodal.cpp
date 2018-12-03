#include "bookentryuppermodal.h"
#include "ui_bookentryuppermodal.h"
#include <QIcon>

bookEntryUpperModal::bookEntryUpperModal(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::bookEntryUpperModal)
{
    ui->setupUi(this);
    QIcon icon = ui->cancel->icon();
    icon.addPixmap(QPixmap(":/icons/return_white.png"), QIcon::Normal);
    ui->cancel->setIcon(icon);
    icon = ui->confirm->icon();
    icon.addPixmap(QPixmap(":/icons/ok_white.png"), QIcon::Normal);
    ui->confirm->setIcon(icon);
}

bookEntryUpperModal::~bookEntryUpperModal()
{
    delete ui;
}

void bookEntryUpperModal::setTime(QDateTime time){
    ui->time->setText(time.toString("yyyy-MM-dd hh:mm:ss"));
}

void bookEntryUpperModal::setPage(int lastIndex, int total){
    ui->pageinfo->setText(tr("Page %1/%2").arg(QString::number(lastIndex + 1), QString::number(total)));
}

void bookEntryUpperModal::setLastRead(QString content){
    ui->introduction->setText(content);
}

QPushButton *bookEntryUpperModal::confirmButton(){
    return ui->confirm;
}

QPushButton *bookEntryUpperModal::cancelButton(){
    return ui->cancel;
}


void bookEntryUpperModal::setName(QString name){
    ui->name->setText(name);
}

QString bookEntryUpperModal::getName(){
    return ui->name->text();
}

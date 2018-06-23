#include "bookentrymodal.h"
#include "ui_bookentrymodal.h"
#include <QIcon>
#include <iostream>

bookEntryModal::bookEntryModal(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::bookEntryModal)
{
    ui->setupUi(this);
    QIcon icon = ui->cancel->icon();
    icon.addPixmap(QPixmap(":/icons/return_white.png"), QIcon::Normal);
    ui->cancel->setIcon(icon);
    icon = ui->confirm->icon();
    icon.addPixmap(QPixmap(":/icons/ok_white.png"), QIcon::Normal);
    ui->confirm->setIcon(icon);
}

bookEntryModal::~bookEntryModal()
{
    delete ui;
}

void bookEntryModal::setTime(QDateTime time){
    ui->time->setText(time.toString("yyyy-MM-dd hh:mm:ss"));
}

void bookEntryModal::setPage(int lastIndex, int total){
    ui->pageinfo->setText(tr("Page %1/%2").arg(QString::number(lastIndex + 1), QString::number(total)));
}

void bookEntryModal::setLastRead(QString content){
    ui->introduction->setText(content);
}

QPushButton *bookEntryModal::confirmButton(){
    return ui->confirm;
}

QPushButton *bookEntryModal::cancelButton(){
    return ui->cancel;
}

void bookEntryModal::setName(QString name){
    ui->name->setText(name);
}

QString bookEntryModal::getName(){
    return ui->name->text();
}

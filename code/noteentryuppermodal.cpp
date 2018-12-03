#include "noteentryuppermodal.h"
#include "ui_noteentryuppermodal.h"
#include <QIcon>

noteEntryUpperModal::noteEntryUpperModal(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::noteEntryUpperModal)
{
    ui->setupUi(this);
    QIcon icon = ui->cancel->icon();
    icon.addPixmap(QPixmap(":/icons/return_white.png"), QIcon::Normal);
    ui->cancel->setIcon(icon);
    icon = ui->confirm->icon();
    icon.addPixmap(QPixmap(":/icons/ok_white.png"), QIcon::Normal);
    ui->confirm->setIcon(icon);
}

noteEntryUpperModal::~noteEntryUpperModal()
{
    delete ui;
}

void noteEntryUpperModal::setTime(QDateTime time){
    ui->time->setText(time.toString("yyyy-MM-dd hh:mm:ss"));
}

void noteEntryUpperModal::setIntroduction(QString content){
    ui->introduction->setText(content);
}

QPushButton *noteEntryUpperModal::confirmButton(){
    return ui->confirm;
}

QPushButton *noteEntryUpperModal::cancelButton(){
    return ui->cancel;
}

void noteEntryUpperModal::setName(QString name){
    ui->name->setText(name);
}

QString noteEntryUpperModal::getName(){
    return ui->name->text();
}

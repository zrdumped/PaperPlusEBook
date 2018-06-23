#include "noteentrymodal.h"
#include "ui_noteentrymodal.h"
#include <QIcon>

noteEntryModal::noteEntryModal(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::noteEntryModal)
{
    ui->setupUi(this);
    QIcon icon = ui->cancel->icon();
    icon.addPixmap(QPixmap(":/icons/return_white.png"), QIcon::Normal);
    ui->cancel->setIcon(icon);
    icon = ui->confirm->icon();
    icon.addPixmap(QPixmap(":/icons/ok_white.png"), QIcon::Normal);
    ui->confirm->setIcon(icon);
}

noteEntryModal::~noteEntryModal()
{
    delete ui;
}

void noteEntryModal::setTime(QDateTime time){
    ui->time->setText(time.toString("yyyy-MM-dd hh:mm:ss"));
}

void noteEntryModal::setIntroduction(QString content){
    ui->introduction->setText(content);
}

QPushButton *noteEntryModal::confirmButton(){
    return ui->confirm;
}

QPushButton *noteEntryModal::cancelButton(){
    return ui->cancel;
}

void noteEntryModal::setName(QString name){
    ui->name->setText(name);
}

QString noteEntryModal::getName(){
    return ui->name->text();
}

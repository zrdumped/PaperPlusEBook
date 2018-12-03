#include "noteentryeditupper.h"
#include "ui_noteentryeditupper.h"
#include <QIcon>
#include <QPlainTextEdit>
#include <QLineEdit>
noteEntryEditUpper::noteEntryEditUpper(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::noteEntryEditUpper)
{
    ui->setupUi(this);
    QIcon icon = ui->cancel->icon();
    icon.addPixmap(QPixmap(":/icons/return_white.png"), QIcon::Normal);
    ui->cancel->setIcon(icon);
    icon = ui->confirm->icon();
    icon.addPixmap(QPixmap(":/icons/ok_white.png"), QIcon::Normal);
    ui->confirm->setIcon(icon);
}

noteEntryEditUpper::~noteEntryEditUpper()
{
    delete ui;
}

QString noteEntryEditUpper::getIntroduction(){
    return ui->introduction->toPlainText();
}

QPushButton *noteEntryEditUpper::confirmButton(){
    return ui->confirm;
}

QPushButton *noteEntryEditUpper::cancelButton(){
    return ui->cancel;
}

QString noteEntryEditUpper::getName(){
    return ui->name->text();
}

void noteEntryEditUpper::reset(){
    ui->name->setText("");
    ui->introduction->setPlainText("");
}

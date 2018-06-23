#include "noteentryedit.h"
#include "ui_noteentryedit.h"
#include <QIcon>
#include <QPlainTextEdit>
noteEntryEdit::noteEntryEdit(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::noteEntryEdit)
{
    ui->setupUi(this);
    QIcon icon = ui->cancel->icon();
    icon.addPixmap(QPixmap(":/icons/return_white.png"), QIcon::Normal);
    ui->cancel->setIcon(icon);
    icon = ui->confirm->icon();
    icon.addPixmap(QPixmap(":/icons/ok_white.png"), QIcon::Normal);
    ui->confirm->setIcon(icon);
}

noteEntryEdit::~noteEntryEdit()
{
    delete ui;
}

QString noteEntryEdit::getIntroduction(){
    return ui->introduction->toPlainText();
}

QPushButton *noteEntryEdit::confirmButton(){
    return ui->confirm;
}

QPushButton *noteEntryEdit::cancelButton(){
    return ui->cancel;
}

QString noteEntryEdit::getName(){
    return ui->name->text();
}

void noteEntryEdit::reset(){
    ui->name->setText("");
    ui->introduction->setPlainText("");
}

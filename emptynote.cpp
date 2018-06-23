#include "emptynote.h"
#include "ui_emptynote.h"

EmptyNote::EmptyNote(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::EmptyNote)
{
    ui->setupUi(this);
    QIcon icon = ui->addNote->icon();
    icon.addPixmap(QPixmap(":/icons/plus.png"), QIcon::Normal);
    ui->addNote->setIcon(icon);
}

EmptyNote::~EmptyNote()
{
    delete ui;
}

QPushButton *EmptyNote::addNoteBtn(){
    return ui->addNote;
}

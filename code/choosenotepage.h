#ifndef CHOOSENOTEPAGE_H
#define CHOOSENOTEPAGE_H

#include <QFrame>
#include <QPushButton>

namespace Ui {
class ChooseNotePage;
}

class ChooseNotePage : public QFrame
{
    Q_OBJECT

public:
    explicit ChooseNotePage(QWidget *parent = 0);
    ~ChooseNotePage();
    QPushButton *addNoteBtn();
    QPushButton *returnBtn();
    void setBookName(QString bookName);
private:
    Ui::ChooseNotePage *ui;
};

#endif // CHOOSENOTEPAGE_H

#ifndef CHOOSENOTEPAGE_H
#define CHOOSENOTEPAGE_H

#include <QFrame>

namespace Ui {
class ChooseNotePage;
}

class ChooseNotePage : public QFrame
{
    Q_OBJECT

public:
    explicit ChooseNotePage(QWidget *parent = 0);
    ~ChooseNotePage();

private:
    Ui::ChooseNotePage *ui;
};

#endif // CHOOSENOTEPAGE_H

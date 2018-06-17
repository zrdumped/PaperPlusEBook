#ifndef EMPTYBOOK_H
#define EMPTYBOOK_H

#include <QFrame>

namespace Ui {
class EmptyBook;
}

class EmptyBook : public QFrame
{
    Q_OBJECT

public:
    explicit EmptyBook(QWidget *parent = 0);
    ~EmptyBook();

private:
    Ui::EmptyBook *ui;
};

#endif // EMPTYBOOK_H

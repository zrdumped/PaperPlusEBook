#ifndef EMPTYBOOK_H
#define EMPTYBOOK_H

#include <QFrame>
#include <QPushButton>
namespace Ui {
class EmptyBook;
}

class EmptyBook : public QFrame
{
    Q_OBJECT

public:
    explicit EmptyBook(QWidget *parent = 0);
    ~EmptyBook();
    QPushButton *addBookBtn();
private:
    Ui::EmptyBook *ui;
};

#endif // EMPTYBOOK_H

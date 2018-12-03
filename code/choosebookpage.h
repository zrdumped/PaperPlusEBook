#ifndef CHOOSEBOOKPAGE_H
#define CHOOSEBOOKPAGE_H

#include <QFrame>
#include <QPushButton>
namespace Ui {
class ChooseBookPage;
}

class ChooseBookPage : public QFrame
{
    Q_OBJECT

public:
    explicit ChooseBookPage(QWidget *parent = 0);
    ~ChooseBookPage();
     QPushButton *addBookBtn();
private:
    Ui::ChooseBookPage *ui;
};

#endif // CHOOSEBOOKPAGE_H

#ifndef CHOOSEBOOKPAGE_H
#define CHOOSEBOOKPAGE_H

#include <QFrame>

namespace Ui {
class ChooseBookPage;
}

class ChooseBookPage : public QFrame
{
    Q_OBJECT

public:
    explicit ChooseBookPage(QWidget *parent = 0);
    ~ChooseBookPage();

private:
    Ui::ChooseBookPage *ui;
};

#endif // CHOOSEBOOKPAGE_H

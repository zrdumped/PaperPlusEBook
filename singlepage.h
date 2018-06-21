#ifndef LEFTPAGE_H
#define LEFTPAGE_H

#include <QFrame>
#include <QString>

namespace Ui {
class SinglePage;
}

class SinglePage : public QFrame
{
    Q_OBJECT

public:
    explicit SinglePage(QWidget *parent = 0);
    ~SinglePage();
    void setContent(QString content, int pageNumber, int totalPageNumber = -1);
    void setTotalPageNumber(int totalPageNumber);
    void setPageNumberEmpty();
private:
    Ui::SinglePage *ui;
    int totalPageNumber = 0;
};

#endif // LEFTPAGE_H

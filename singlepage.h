#ifndef LEFTPAGE_H
#define LEFTPAGE_H

#include <QFrame>
#include <QString>
#include <QLabel>
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
    void setNote(QImage img);
    QImage getNote();
    void clearNote();
private:
    Ui::SinglePage *ui;
    QLabel *note;
    QImage noteImage;
    int totalPageNumber = 0;
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // LEFTPAGE_H

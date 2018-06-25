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
    void setPainter(QColor color, int width);
    void cleanDotHistory();
private:
    Ui::SinglePage *ui;
    QLabel *note;
    QImage noteImage;
    QPoint lastPoint;
    QPoint thisPoint;
    int totalPageNumber = 0;
    QColor painterColor;
    int painterWidth = 0;
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // LEFTPAGE_H

#ifndef ARROWWIDGET_H
#define ARROWWIDGET_H

#include <QWidget>

class ArrowWidget : public QWidget
{
    Q_OBJECT

public:
    ArrowWidget(QWidget *parent = 0);

    // 设置小三角起始位置;
    void setStartPos(int startX);

    // 设置小三角宽和高;
    void setTriangleInfo(int width, int height);

    // 设置中间区域widget;
    void setCenterWidget(QWidget* widget);

protected:
    void paintEvent(QPaintEvent *);

private:
    // 小三角起始位置;
    int startX;
    int shadowWidth = 15;
    int triangleWidth = 15;
    int triangleHeight = 15;
    int borderRadius = 15;
};

#endif // ARROWWIDGET_H

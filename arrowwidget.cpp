#include "arrowwidget.h"
#include <qhboxlayout>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

ArrowWidget::ArrowWidget(QWidget *parent)
    : QWidget(parent)
    , startX(50)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // 设置阴影边框;
    auto shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor(Qt::gray);
    shadowEffect->setBlurRadius(shadowWidth);
    this->setGraphicsEffect(shadowEffect);

    setFixedSize(150, 200);
}

void ArrowWidget::setCenterWidget(QWidget* widget)
{
    QHBoxLayout* hMainLayout = new QHBoxLayout(this);
    hMainLayout->addWidget(widget);
    hMainLayout->setSpacing(0);
    hMainLayout->setContentsMargins(shadowWidth, shadowWidth + triangleHeight, shadowWidth, shadowWidth);
}

// 设置小三角显示的起始位置;
void ArrowWidget::setStartPos(int startX)
{
    startX = startX;
}

void ArrowWidget::setTriangleInfo(int width, int height)
{
    triangleWidth = width;
    triangleHeight = height;
}

void ArrowWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255));

    // 小三角区域;
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(startX, triangleHeight + shadowWidth);
    trianglePolygon << QPoint(startX + triangleWidth / 2, shadowWidth);
    trianglePolygon << QPoint(startX + triangleWidth, triangleHeight + shadowWidth);

    QPainterPath drawPath;
    drawPath.addRoundedRect(QRect(shadowWidth, triangleHeight + shadowWidth,\
                                width() - shadowWidth * 2, height() - shadowWidth * 2 - triangleHeight),\
                                borderRadius, borderRadius);
    // Rect + Triangle;
    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
}

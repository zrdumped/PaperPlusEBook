#ifndef IMAGECONFIG_H
#define IMAGECONFIG_H

#include <mycv.h>
#include <QMainWindow>
#include "QLabel"
#include "QMouseEvent"
#include "QFileDialog"
#include <qstatusbar.h>

namespace Ui {
class ImageConfig;
}

class ImageConfig : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageConfig(QMainWindow *parent = 0);
    ~ImageConfig();

private:
    Ui::ImageConfig *ui;
    QLabel* rectLabel;
    QImage rectQImage;
    Mat rectMat;

    void ReactangleCalibration();
    QImage ShowImage(Mat src, QLabel* label, QImage::Format format);

protected:
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // IMAGECONFIG_H

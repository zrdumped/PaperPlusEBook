#ifndef IMAGECONFIG_H
#define IMAGECONFIG_H

#include <QWidget>

namespace Ui {
class ImageConfig;
}

class ImageConfig : public QWidget
{
    Q_OBJECT

public:
    explicit ImageConfig(QWidget *parent = 0);
    ~ImageConfig();

private:
    Ui::ImageConfig *ui;
};

#endif // IMAGECONFIG_H

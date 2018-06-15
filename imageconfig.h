#ifndef IMAGECONFIG_H
#define IMAGECONFIG_H

#include <QMainWindow>

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
};

#endif // IMAGECONFIG_H

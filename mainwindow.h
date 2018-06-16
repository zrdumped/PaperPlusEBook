#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imageconfig.h"
#include <QMainWindow>
#include <fstream>
//#include <poppler/cpp/poppler-document.h>
//#include <poppler/cpp/poppler-page.h>
#ifdef _WIN32
   //define something for Windows (32-bit and 64-bit, this part is common)

    //#include "poppler/poppler-qt5.h"


   #ifdef _WIN64
      //define something for Windows (64-bit only)
   #endif
#elif __APPLE__
   #include "poppler-qt5/qt5/src/poppler-qt5.h"
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void normalWarning(QString msg);
    void normalInformation(QString msg);
    bool normalDecision(QString msg);
    int InitPageNumber();
    int SetPage();
    int turnover(int pages);
    int AddPageNumber(int number);
public Q_SLOTS:
    void OpenImageConfigureWindow();

private:
    Ui::MainWindow *ui;
    ImageConfig *window;
    int left_page_num = 0;
    QString book_name;
    int pg_width = 480;
    int pg_height = 640;
    int res_x = 72;
    int res_y = 72;
    int base_offset = 0;
    int book_page_num = 100;
    //poppler::document *book;
    //Poppler::Document *book;
    int each_page_bytes = 400;
    //Poppler::Document *book;
    std::fstream book;
private slots:
    void SelectBook();
    void SetOffset();
    void SetOffsetTmp();
};

#endif // MAINWINDOW_H

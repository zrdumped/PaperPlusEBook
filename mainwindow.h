#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imageconfig.h"
#include <fstream>
#include <QColor>
#include <QString>
#include <menu.h>
#include <arrowwidget.h>
#include <choosebookpage.h>
#include <choosenotepage.h>
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


private:
    Ui::MainWindow *ui;
    ImageConfig *window;
    Menu *bookMenu;
    Menu *noteMenu;
    ArrowWidget *penStyle;
    ArrowWidget *eraserStyle;
    ArrowWidget *offsetSetter;
    ChooseBookPage *choosebookpage;
    ChooseNotePage *choosenotepage;
    int left_page_num = 0;
    QString book_name;
    int base_offset = 0;
    int book_page_num = 100;
    //poppler::document *book;
    //Poppler::Document *book;
    //int each_page_bytes = 400;
    //Poppler::Document *book;
    std::fstream book;
    int sidePaddingWidth = 80;
    int middlePaddingWidth = 80;
    int qzxingSideLength = 80;
    int iconSideLength = 40;
    QString dayLightStyle = "background-color: rgb(249, 245, 232);color: rgb(38, 38, 38);";
    QString nightLightStyle = "background-color: rgb(11, 11, 11);color: rgb(59, 59, 59);";
    bool isDayLighting = false;
    void showAllUIs();
    void hideAllUIs();
private slots:
    void SelectBook();
    void SetOffset();
    void SetOffsetTmp();
    void OpenImageConfigureWindow();
    void changeLightingMode();
};

#endif // MAINWINDOW_H

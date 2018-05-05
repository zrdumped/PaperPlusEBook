#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "poppler-qt5/qt5/src/poppler-qt5.h"

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
    int left_page_num = 0;
    QString book_name;
    int pg_width = 100;
    int pg_height = 200;
    int base_offset = 0;
    int book_page_num = 100;

    //Poppler::Document *book;
private slots:
    void SelectBook();
    void SetOffset();
};

#endif // MAINWINDOW_H

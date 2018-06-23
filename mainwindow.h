#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imageconfig.h"
#include <QMainWindow>
#include <fstream>
#include <QColor>
#include <QString>
#include <menu.h>
#include <arrowwidget.h>
#include <choosebookpage.h>
#include <choosenotepage.h>
#include <emptybook.h>
#include <emptynote.h>
#include <singlepage.h>
#include <bookmanager.h>
#include <noteentryedit.h>
#include <noteentryeditupper.h>
#include <noteentrymodal.h>
#include <noteentryuppermodal.h>
#include <bookentrymodal.h>
#include <bookentryuppermodal.h>
#include <QStackedLayout>
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
    void turnToPageWithLeftPageNumber(int pageNumber);
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
    EmptyBook *emptybookpage;
    EmptyNote *emptynotepage;
    SinglePage *leftPage;
    SinglePage *rightPage;
    QStackedLayout *leftPageStack;
    QStackedLayout *rightPageStack;
    QPushButton *whitePanel;
    QWidget *currentActive;
    QString currentActiveName;
    bookEntryModal *bookentrymodal;
    bookEntryUpperModal *bookentryuppermodal;
    noteEntryModal *noteentrymodal;
    noteEntryUpperModal *noteentryuppermodal;
    noteEntryEdit *noteentryedit;
    noteEntryEditUpper *noteentryeditupper;
    BookManager bookmanager;
    int leftPageNumPhysical = 1;
    int baseOffset = 0;
    int bookPageNum = 100;
    int sampleNumber = 100;
    std::fstream book;
    int entryPerPage = 8;
    int sidePaddingWidth = 140;
    int middlePaddingWidth = 80;
    int qzxingSideLength = 80;
    int iconSideLength = 40;
    int charPerLine = 20;
    int linePerPage = 20;
    int margin = 12;
    QString dayLightStyle = "background-color: rgb(249, 245, 232);color: rgb(38, 38, 38);";
    QString nightLightStyle = "background-color: rgb(11, 11, 11);color: rgb(59, 59, 59);";
    bool isDayLighting = false;
    int penWidth = 6;
    int eraserWidth = 6;
    QColor penColor = Qt::red;
    void showAllUIs();
    void hideAllUIs();
    void loadAllBookEntries();
    void loadAllNoteEntries();
    void addBookBtn(QString bookName);
    void addNoteBtn(QString noteName);
    void startReading();
    void leaveReading(QString name, QWidget *widget);
    void autoSaveNote();
private slots:
    void OpenImageConfigureWindow();
    void changeLightingMode();
    void createNewBook();
    void backToRead();
    void selectBook();
    void selectNote();
    void createNewNote();
    void showBookInfoModal();
    void showNoteInfoModal();
    void backToSelectBook();
    void backToSelectNote();
    void addNote();
    void addNoteUp();
    void usePen();
    void useEraser();
};

#endif // MAINWINDOW_H

#ifndef MENU_H
#define MENU_H
#include <vector>
#include <QFrame>
#include <QWidget>
#include <QString>
namespace Ui {
class Menu;
}

class Menu : public QFrame
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0, int entriesNumPerPage = 6);
    ~Menu();
    void addEntry(QWidget *newEntry);
    void resetEntries();
    int getCount();
    bool isTopHalf(QWidget *entry);
    QRect getNextGeometry(QPushButton *btn);
private:
    Ui::Menu *ui;
    int entriesPerPage = 6;
    std::vector<QWidget *> entries;
    int currentPageIndex = 0;
    int pages = 0;
    void changeUI();
private slots:
    void gotoNextPage();
    void gotoPrevPage();
    void gotoFirstPage();
    void gotoLastPage();
};

#endif // MENU_H

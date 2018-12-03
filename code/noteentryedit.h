#ifndef NOTEENTRYEDIT_H
#define NOTEENTRYEDIT_H
#include <QPushButton>
#include <QFrame>

namespace Ui {
class noteEntryEdit;
}

class noteEntryEdit : public QFrame
{
    Q_OBJECT

public:
    explicit noteEntryEdit(QWidget *parent = 0);
    ~noteEntryEdit();
    QString getIntroduction();
    QPushButton *confirmButton();
    QPushButton *cancelButton();
    QString getName();
    void reset();
private:
    Ui::noteEntryEdit *ui;
};

#endif // NOTEENTRYEDIT_H

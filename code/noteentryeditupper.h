#ifndef NOTEENTRYEDITUPPER_H
#define NOTEENTRYEDITUPPER_H
#include <QPushButton>
#include <QFrame>

namespace Ui {
class noteEntryEditUpper;
}

class noteEntryEditUpper : public QFrame
{
    Q_OBJECT

public:
    explicit noteEntryEditUpper(QWidget *parent = 0);
    ~noteEntryEditUpper();
    QString getIntroduction();
    QPushButton *confirmButton();
    QPushButton *cancelButton();
    QString getName();
    void reset();
private:
    Ui::noteEntryEditUpper *ui;
};

#endif // NOTEENTRYEDITUPPER_H

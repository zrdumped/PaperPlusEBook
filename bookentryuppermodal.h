#ifndef BOOKENTRYUPPERMODAL_H
#define BOOKENTRYUPPERMODAL_H
#include <QDateTime>
#include <QPushButton>
#include <QFrame>

namespace Ui {
class bookEntryUpperModal;
}

class bookEntryUpperModal : public QFrame
{
    Q_OBJECT

public:
    explicit bookEntryUpperModal(QWidget *parent = 0);
    ~bookEntryUpperModal();
    void setTime(QDateTime time);
    void setPage(int lastIndex, int total);
    void setLastRead(QString content);
    void setName(QString name);
    QString getName();
    QPushButton *confirmButton();
    QPushButton *cancelButton();

private:
    Ui::bookEntryUpperModal *ui;
};

#endif // BOOKENTRYUPPERMODAL_H

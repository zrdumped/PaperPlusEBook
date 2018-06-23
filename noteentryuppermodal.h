#ifndef NOTEENTRYUPPERMODAL_H
#define NOTEENTRYUPPERMODAL_H
#include <QDateTime>
#include <QPushButton>
#include <QFrame>

namespace Ui {
class noteEntryUpperModal;
}

class noteEntryUpperModal : public QFrame
{
    Q_OBJECT

public:
    explicit noteEntryUpperModal(QWidget *parent = 0);
    ~noteEntryUpperModal();
    void setTime(QDateTime time);
    void setIntroduction(QString content);
    QPushButton *confirmButton();
    QPushButton *cancelButton();
    void setName(QString name);
    QString getName();
private:
    Ui::noteEntryUpperModal *ui;
};

#endif // NOTEENTRYUPPERMODAL_H

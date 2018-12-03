#ifndef NOTEENTRYMODAL_H
#define NOTEENTRYMODAL_H
#include <QDateTime>
#include <QPushButton>
#include <QFrame>

namespace Ui {
class noteEntryModal;
}

class noteEntryModal : public QFrame
{
    Q_OBJECT

public:
    explicit noteEntryModal(QWidget *parent = 0);
    ~noteEntryModal();
    void setTime(QDateTime time);
    void setIntroduction(QString content);
    QPushButton *confirmButton();
    QPushButton *cancelButton();
    void setName(QString name);
    QString getName();
private:
    Ui::noteEntryModal *ui;
};

#endif // NOTEENTRYMODAL_H

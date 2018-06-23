#ifndef BOOKENTRYMODAL_H
#define BOOKENTRYMODAL_H
#include <QDateTime>
#include <QFrame>
#include <QPushButton>
namespace Ui {
class bookEntryModal;
}

class bookEntryModal : public QFrame
{
    Q_OBJECT

public:
    explicit bookEntryModal(QWidget *parent = 0);
    ~bookEntryModal();
    void setTime(QDateTime time);
    void setPage(int lastIndex, int total);
    void setLastRead(QString content);
    void setName(QString name);
    QString getName();
    QPushButton *confirmButton();
    QPushButton *cancelButton();
    QRect getOffsets(QWidget *parent);
private:
    Ui::bookEntryModal *ui;
};

#endif // BOOKENTRYMODAL_H

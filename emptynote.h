#ifndef EMPTYNOTE_H
#define EMPTYNOTE_H

#include <QFrame>

namespace Ui {
class EmptyNote;
}

class EmptyNote : public QFrame
{
    Q_OBJECT

public:
    explicit EmptyNote(QWidget *parent = 0);
    ~EmptyNote();

private:
    Ui::EmptyNote *ui;
};

#endif // EMPTYNOTE_H

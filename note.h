#ifndef NOTE_H
#define NOTE_H
#include <QString>
#include <QDir>
#include <QFile>

class Note
{
/*
 * Note is actually a folder
 */
public:
    Note();
    Note(QString bookDirPath, QString noteName);
    void chooseNote(QString bookDirPath, QString noteName);
    QString getNoteName();
private:
    QDir noteDir;
};

#endif // NOTE_H

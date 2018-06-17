#ifndef NOTE_H
#define NOTE_H
#include <QString>
#include <QDir>
#include <QFile>
#include <QImage>
#include <notemetadata.h>
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
    QString getIntroduction();
    QImage getNotePage(int page);
    void storeNotePage(QImage &img, int page);
private:
    QDir noteDir;
    QString extension = ".png";
    NoteMetadata notemetadata;
};

#endif // NOTE_H

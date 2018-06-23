#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H
#include <QString>
#include <map>
#include <note.h>
class NoteManager
{
public:
    NoteManager();
    void loadAllNotes(QString bookName);
    int addNote(QString noteName, QString introduction);
    void switchNote(QString noteName);
    std::vector<Note> getAllNotes();
    QImage getNotePage(int p);
    QString getName();
    Note getSingleNote(QString name);
    void storeNotePage(QImage &img, int p);
private:
    QString bookName;
    std::map<QString, Note> noteMap;
    QString currentNote;
};

#endif // NOTEMANAGER_H

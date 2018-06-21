#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H
#include <QString>
#include <map>
#include <note.h>
class NoteManager
{
public:
    NoteManager();
    void getNotes(QString bookName);
    void addNote(QString noteName, QString introduction);
    void switchNote(QString noteName);
private:
    std::map<QString, Note> noteMap;

};

#endif // NOTEMANAGER_H

#include "note.h"

Note::Note()
{

}

Note::Note(QString bookDirPath, QString noteName)
{
    noteDir.setPath(bookDirPath + "/" + noteName);
}

void Note::chooseNote(QString bookDirPath, QString noteName){
    noteDir.setPath(bookDirPath + "/" + noteName);
}



QString Note::getNoteName(){
    return noteDir.dirName();
}

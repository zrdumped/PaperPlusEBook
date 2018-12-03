#include "note.h"
#include <iostream>
Note::Note()
{

}

Note::Note(QString bookDirPath, QString noteName)
{
    noteDir.setPath(bookDirPath + "/" + noteName);
    notemetadata.loadMeta(noteDir.absolutePath());
}

void Note::chooseNote(QString bookDirPath, QString noteName){
    noteDir.setPath(bookDirPath + "/" + noteName);
    notemetadata.loadMeta(noteDir.absolutePath());
}

QString Note::getNoteName(){
    return noteDir.dirName();
}

QImage Note::getNotePage(int page){
    QString imgName = QString::number(page) + extension;
    QFile f(noteDir.absoluteFilePath(imgName));
    if(f.exists()){
        return QImage(noteDir.absoluteFilePath(imgName));
    }
    else{
        return QImage();
    }
}

void Note::storeNotePage(QImage &img, int page){
    QString imgName = QString::number(page) + extension;
    img.save(noteDir.absoluteFilePath(imgName));
    std::cout<<"savepng"<<noteDir.absoluteFilePath(imgName).toStdString()<<std::endl;
    notemetadata.setLastModifiedTime(QFileInfo(noteDir.absolutePath()).lastModified());
}

QString Note::getIntroduction(){
    return notemetadata.getIntroduction();
}

QDateTime Note::getLastModifiedTime(){
    return notemetadata.getLastModifiedTime();
}

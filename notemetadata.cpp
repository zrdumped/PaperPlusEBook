#include "notemetadata.h"
#include <fstream>
#include <QDir>
#include <QFileInfo>
#include <txtparser.h>
#include <iostream>
NoteMetadata::NoteMetadata()
{

}

NoteMetadata::NoteMetadata(QString notepath){
    loadMeta(notepath);
}

bool NoteMetadata::loadMeta(QString notepath){
    notePath = notepath;
    QDir d(notepath);
    QFileInfo f(notepath);
    QString metaname = f.fileName()+extension;
    std::ifstream meta(d.absoluteFilePath(metaname).toLocal8Bit().toStdString().c_str(), std::fstream::in);
    if(!meta.is_open())
        return 0;
    charandint ci;
    ci.i = 0;
    meta.read(ci.c, 4);
    int len = ci.i;
    char *p = (char *)malloc(len);
    meta.read(p, len);
    introduction = QString::fromStdString(std::string(p, len));
    free(p);
    lastModifiedTime = f.lastModified();
    meta.close();
    return 1;
}

QDateTime NoteMetadata::getLastModifiedTime(){
    return lastModifiedTime;
}

void NoteMetadata::setLastModifiedTime(QDateTime dt){
    lastModifiedTime = dt;
}

QString NoteMetadata::getIntroduction(){
    return introduction;
}

void NoteMetadata::setIntroduction(QString intro){
    introduction = intro;
}

void NoteMetadata::storeMeta(){
    std::cout<<"notepath: "<<notePath.toStdString()<<std::endl;
    QDir d(notePath);
    QFileInfo f(notePath);
    QString metaname = f.fileName()+extension;
    std::ofstream meta(d.absoluteFilePath(metaname).toLocal8Bit().toStdString().c_str(), std::fstream::out|std::fstream::trunc);
    charandint ci;
    std::string p = introduction.toStdString();
    ci.i = p.length();
    meta.write(ci.c, 4);
    meta.write(p.c_str(), ci.i);
    meta.flush();
    meta.close();
}

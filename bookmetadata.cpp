#include "bookmetadata.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <fstream>
#include <txtparser.h>
#include <iostream>
BookMetadata::BookMetadata()
{
    bookName = "";
    bookFullPath = "";
    metaFullPath = "";
    bookPageCount = 0;
    lastReadPage = 0;
    lastReadTime = QDateTime();
}

BookMetadata::BookMetadata(QString fullPath, unsigned int pageCount, unsigned int lastRead){
    bookFullPath = fullPath;
    QFileInfo f(fullPath);
    bookName = f.fileName().split(".")[0];
    metaFullPath = f.absoluteDir().absolutePath() + "/" + bookName + extension;
    bookPageCount = pageCount;
    lastReadPage = lastRead;
}

QString BookMetadata::getBookPath(){
    return bookFullPath;
}

QString BookMetadata::getBookName(){
    return bookName;
}

void BookMetadata::setBookPath(QString path){
    bookFullPath = path;
    QFileInfo f(path);
    bookName = f.fileName().split(".")[0];
    metaFullPath = f.absoluteDir().absolutePath() + "/" + bookName + extension;
}

unsigned int BookMetadata::getBookPageCount(){
    return bookPageCount;
}

void BookMetadata::setBookPageCount(unsigned int pageCount){
    bookPageCount = pageCount;
}

unsigned int BookMetadata::getLastReadPage(){
    return lastReadPage;
}

void BookMetadata::setLastReadPage(unsigned int lastRead){
    lastReadPage = lastRead;
}

QDateTime BookMetadata::getLastReadTime(){
    return lastReadTime;
}

void BookMetadata::setLastReadTime(QDateTime dt){
    lastReadTime = dt;
}

bool BookMetadata::loadMeta(QString bookpath){
    setBookPath(bookpath);
    std::ifstream meta(metaFullPath.toLocal8Bit().toStdString().c_str(), std::fstream::in);
    if(!meta.is_open())
        return 0;
    TxtParser::charandint ci;
    ci.i = 0;
    meta.read(ci.c, 4);
    int len = ci.i;
    char *p = (char *)malloc(len);
    meta.read(p, len);
    bookFullPath = QString::fromStdString(std::string(p, len));
    free(p);
    meta.read(ci.c, 4);
    bookPageCount = ci.i;
    meta.read(ci.c, 4);
    lastReadPage = ci.i;
    meta.close();
    QFileInfo info(bookFullPath);
    lastReadTime = info.lastRead();
    return 1;
}

void BookMetadata::storeMeta(){
    std::ofstream meta(metaFullPath.toLocal8Bit().toStdString().c_str(), std::fstream::out|std::fstream::trunc);
    TxtParser::charandint ci;
    std::string p = bookFullPath.toStdString();
    ci.i = p.length();
    meta.write(ci.c, 4);
    meta.write(p.c_str(), ci.i);
    ci.i = bookPageCount;
    meta.write(ci.c, 4);
    ci.i = lastReadPage;
    meta.write(ci.c, 4);
    meta.close();
}

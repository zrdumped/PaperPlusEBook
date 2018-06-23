#include "bookmetadata.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <fstream>
#include <txtparser.h>
#include <iostream>
#include <QCoreApplication>
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
    bookName = f.fileName().split("."+f.suffix())[0];
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
    bookName = f.fileName().split("."+f.suffix())[0];
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
    QDir workDir(QCoreApplication::applicationDirPath());
    QFileInfo f(workDir.absoluteFilePath(bookpath));
    bookName = bookpath;
    metaFullPath = f.absoluteFilePath() + "/" + bookName + extension;
    std::ifstream meta(metaFullPath.toLocal8Bit().toStdString().c_str(), std::fstream::in);
    if(!meta.is_open())
        return 0;
    charandint ci;
    ci.i = 0;
    meta.read(ci.c, 4);
    int len = ci.i;
    char *p = (char *)malloc(len);
    meta.read(p, len);
    bookFullPath = QString::fromStdString(std::string(p, len));
    std::cout<<"bookfullpatrh: "<<bookFullPath.toStdString()<<std::endl;
    free(p);
    meta.read(ci.c, 4);
    bookPageCount = ci.i;
    meta.read(ci.c, 4);
    lastReadPage = ci.i;
    meta.read(ci.c, 4);
    char *lst = (char *)malloc(ci.i);
    meta.read(lst, ci.i);
    lastReadTime = QDateTime::fromString(QString::fromStdString(std::string(lst, ci.i)), "yyyy-MM-dd hh:mm:ss");
    free(lst);
    meta.close();
    return 1;
}

void BookMetadata::storeMeta(){
    std::ofstream meta(metaFullPath.toLocal8Bit().toStdString().c_str(), std::fstream::out|std::fstream::trunc);
    charandint ci;
    std::string p = bookFullPath.toStdString();
    ci.i = p.length();
    meta.write(ci.c, 4);
    meta.write(p.c_str(), ci.i);
    ci.i = bookPageCount;
    meta.write(ci.c, 4);
    ci.i = lastReadPage;
    meta.write(ci.c, 4);
    QFileInfo info(bookFullPath);
    lastReadTime = info.lastRead();
    std::string lst = lastReadTime.toString("yyyy-MM-dd hh:mm:ss").toStdString();
    ci.i = lst.length();
    meta.write(ci.c, 4);
    meta.write(lst.c_str(), ci.i);
    meta.close();
}

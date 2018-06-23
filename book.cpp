#include "book.h"
#include <QCoreApplication>
#include <iostream>
#include <QFileInfo>
Book::Book()
{

}

Book::~Book(){
    if(bookFStream.is_open())
        bookFStream.close();
    meta.storeMeta();
    pagemeta.~BookPagedata();
}

int Book::newBook(QString bookPath, QString bookName){
    QDir workDir(QCoreApplication::applicationDirPath());
    QDir bookDir(workDir.absoluteFilePath(bookName));
    if(bookDir.exists())
        return -1;
    int r = workDir.mkdir(bookDir.absolutePath());
    if(!r)
        return -2;
    QString bookFileName = QFileInfo(bookPath).fileName();
    QString newBookPath = bookDir.absoluteFilePath(bookFileName);
    QFile::copy(bookPath, newBookPath);
    meta.setBookPath(newBookPath);
    int pc = TxtParser::ParseFile(newBookPath, pagemeta.getPageDataFileName(newBookPath));
    meta.setBookPageCount(pc);
    meta.setLastReadPage(0);
    meta.setLastReadTime(QFileInfo(newBookPath).lastRead());
    meta.storeMeta();
    notebooks.loadAllNotes(bookName);
    return 0;
}

void Book::loadBook(QString bookName){
    meta.loadMeta(bookName);
    notebooks.loadAllNotes(bookName);
}

void Book::openBook(){
    pagemeta.load(meta.getBookName());
    std::cout<<meta.getBookPath().toLocal8Bit().toStdString()<<std::endl;
    bookFStream.open(meta.getBookPath().toLocal8Bit().toStdString().c_str());
}

void Book::closeBook(){
    pagemeta.unload();
    bookFStream.close();
    meta.setLastReadTime(QFileInfo(meta.getBookPath()).lastRead());
    meta.storeMeta();
}

std::vector<Note> Book::getNotes(){
    return notebooks.getAllNotes();
}

QString Book::getBookPageWithPageNumber(int p){
    if(!bookFStream.is_open())
        openBook();
    unsigned int start = pagemeta.page2Offset(p - 1);
    unsigned int size = pagemeta.page2Offset(p) - start;
    bookFStream.seekg(start);
    return bookFStream.readsome(size);
}

QImage Book::getNotePageWithPageNumber(int p){
    return notebooks.getNotePage(p);
}

void Book::switchNote(QString noteName){
    notebooks.switchNote(noteName);
}

int Book::createNewNote(QString noteName, QString introduction){
    return notebooks.addNote(noteName, introduction);
}

BookMetadata Book::getBookMetaData(){
    return meta;
}

QString Book::getName(){
    return meta.getBookName();
}

QString Book::getNoteName(){
    return notebooks.getName();
}

Note Book::getSingleNote(QString name){
    return notebooks.getSingleNote(name);
}

void Book::setLastRead(int p){
    meta.setLastReadPage(p);
}

int Book::getLastRead(){
    return meta.getLastReadPage();
}

int Book::getPageCount(){
    return meta.getBookPageCount();
}

void Book::storeNotePage(QImage &img, int p){
    notebooks.storeNotePage(img, p);
}

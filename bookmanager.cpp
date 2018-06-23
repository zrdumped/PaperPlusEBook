#include "bookmanager.h"
#include <QCoreApplication>
#include <iostream>
BookManager::BookManager()
{
    QDir d(QCoreApplication::applicationDirPath());
    d.setFilter(QDir::Dirs|QDir::NoDotAndDotDot);
    QFileInfoList l = d.entryInfoList();
    for(auto f:l){
        bookMap[f.fileName()] = new Book();
        bookMap[f.fileName()]->loadBook(f.fileName());
    }
}

std::vector<Book*> BookManager::getAllBooks(){
    std::vector<Book*> books;
    for(std::map<QString, Book*>::iterator it = bookMap.begin(); it != bookMap.end(); it ++){
        books.push_back(it->second);
    }
    return books;
}

std::vector<Note> BookManager::getAllNotes(){
    if(currentBook == "")
        return std::vector<Note>();
    return bookMap[currentBook]->getNotes();
}

int BookManager::addNote(QString name, QString intro){
    return bookMap[currentBook]->createNewNote(name, intro);
}

int BookManager::addBook(QString filepath, QString name){
    if(bookMap.find(name) != bookMap.end())
        return -1;
    currentBook = name;
    bookMap[currentBook] = new Book();
    bookMap[currentBook]->newBook(filepath, name);
    return 0;
}

void BookManager::selectNote(QString name){
    bookMap[currentBook]->switchNote(name);
}

QString BookManager::getBookPageWithPageNumber(int p){
    return bookMap[currentBook]->getBookPageWithPageNumber(p);
}

QImage BookManager::getNotePageWithPageNumber(int p){
    return bookMap[currentBook]->getNotePageWithPageNumber(p);
}

QString BookManager::getBookName(){
    return currentBook;
}

QString BookManager::getNoteName(){
    return bookMap[currentBook]->getNoteName();
}

void BookManager::switchBook(QString name){
    if(currentBook != "")
        bookMap[currentBook]->closeBook();
    currentBook = name;
    bookMap[name]->openBook();
}

Book* BookManager::getSingleBook(QString name){
    return bookMap[name];
}

Note BookManager::getSingleNote(QString name){
    return bookMap[currentBook]->getSingleNote(name);
}

void BookManager::openBook(){
    bookMap[currentBook]->openBook();
}

void BookManager::closeBook(){
    if(currentBook != ""){
        bookMap[currentBook]->closeBook();
    }
}

QString BookManager::fetchLastReadFromBook(QString bookname, int p){
    bookMap[bookname]->openBook();
    QString c = bookMap[bookname]->getBookPageWithPageNumber(p);
    bookMap[bookname]->closeBook();
    return c;
}

void BookManager::setLastRead(int p){
    bookMap[currentBook]->setLastRead(p);
}

int BookManager::getLastRead(){
    return bookMap[currentBook]->getLastRead();
}

int BookManager::getPageCount(){
    return bookMap[currentBook]->getPageCount();
}

void BookManager::storeNotePage(QImage &img, int p){
    if(currentBook == "")
        return;
    bookMap[currentBook]->storeNotePage(img, p);
}

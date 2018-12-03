#include "notemanager.h"
#include <notemetadata.h>
#include <QDir>
#include <QFileInfo>
#include <QCoreApplication>
NoteManager::NoteManager()
{

}

void NoteManager::loadAllNotes(QString bookname){
    QDir workDir(QCoreApplication::applicationDirPath());

    QDir book(workDir.absoluteFilePath(bookname));
    bookName = bookname;
    book.setFilter(QDir::Dirs|QDir::NoDotAndDotDot);
    QFileInfoList notes = book.entryInfoList();
    for(auto note : notes){
        noteMap[note.fileName()] = Note(workDir.absoluteFilePath(bookname), note.fileName());
    }
}

int NoteManager::addNote(QString noteName, QString introduction){
    if(noteMap.find(noteName) != noteMap.end())
        return -1;
    QDir workDir(QCoreApplication::applicationDirPath());

    QDir book(workDir.absoluteFilePath(bookName));
    book.mkdir(noteName);
    NoteMetadata nmeta(book.absoluteFilePath(noteName));
    nmeta.setIntroduction(introduction);
    nmeta.storeMeta();
    Note n(bookName, noteName);
    noteMap[noteName] = n;
    return 0;
}

std::vector<Note> NoteManager::getAllNotes(){
    std::vector<Note> notes;
    for(std::map<QString, Note>::iterator it = noteMap.begin(); it != noteMap.end(); it ++){
        notes.push_back(it->second);
    }
    return notes;
}

void NoteManager::switchNote(QString noteName){
    currentNote = noteName;
}

QImage NoteManager::getNotePage(int p){
    return noteMap[currentNote].getNotePage(p);
}

QString NoteManager::getName(){
    return currentNote;
}

Note NoteManager::getSingleNote(QString name){
    return noteMap[name];
}

void NoteManager::storeNotePage(QImage &img, int p){
    noteMap[currentNote].storeNotePage(img, p);
}

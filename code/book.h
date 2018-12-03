#ifndef BOOK_H
#define BOOK_H
#include <bookmetadata.h>
#include <bookpagedata.h>
#include <note.h>
#include <notemanager.h>
#include <txtparser.h>
#include <QImage>
#include <myifstream.h>
class Book
{
/*
 * Book on disk is a directory, with note directories, a bookmetadatafile, a bookpagedatafile, a book content file.
 */
public:
    Book();
    ~Book();
    int newBook(QString bookPath, QString bookName);
    void loadBook(QString bookName);
    void openBook();
    void closeBook();
    std::vector<Note> getNotes();
    QString getBookPageWithPageNumber(int p);
    QImage getNotePageWithPageNumber(int p);
    void switchNote(QString noteName);
    int createNewNote(QString noteName, QString introduction);
    BookMetadata getBookMetaData();
    QString getName();
    QString getNoteName();
    Note getSingleNote(QString name);
    void setLastRead(int p);
    int getLastRead();
    int getPageCount();
    void storeNotePage(QImage &img, int p);
private:
    BookMetadata meta;
    BookPagedata pagemeta;
    NoteManager notebooks;
    MyIfstream bookFStream;
};

#endif // BOOK_H

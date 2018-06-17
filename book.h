#ifndef BOOK_H
#define BOOK_H
#include <bookmetadata.h>
#include <bookpagedata.h>
#include <note.h>
#include <txtparser.h>
class Book
{
/*
 * Book on disk is a directory, with note directories, a bookmetadatafile, a bookpagedatafile, a book content file.
 */
public:
    Book();
private:
    BookMetadata meta;
    BookPagedata pagemeta;
    Note notebook;
public:
    int CreateNewBook(QString bookPath, QString bookName);
    int loadBook(QString bookName);

};

#endif // BOOK_H

#ifndef BOOKMETADATA_H
#define BOOKMETADATA_H
#include <QString>
#include <QDateTime>

class BookMetadata
{
/* The file name of metadata looks like this: bookName.bookmeta
 * file format: length of bookname |   bookname   | pageCount | lastReadPage
 *                    4 bytes      | length bytes |  4 bytes  |   4 bytes
 * Properties:
 * bookPath: the filename of the 'book', including extension
 * bookPageCount: quantity of book pages
 * lastReadPage: the index of the page read most recently
 */
public:
    BookMetadata();
    BookMetadata(QString fullPath, unsigned int pageCount, unsigned int lastRead = 0);
    QString getBookName();
    QString getBookPath();
    void setBookPath(QString path);
    unsigned int getBookPageCount();
    void setBookPageCount(unsigned int pageCount);
    unsigned int getLastReadPage();
    void setLastReadPage(unsigned int lastRead);
    bool loadMeta(QString bookpath);
    void storeMeta();
    QDateTime getLastReadTime();
    void setLastReadTime(QDateTime dt);
private:
    QString bookName;
    QString bookFullPath;
    QString metaFullPath;
    unsigned int bookPageCount;
    unsigned int lastReadPage;
    QDateTime lastReadTime;
    QString extension = ".bookmeta";
};

#endif // BOOKMETADATA_H

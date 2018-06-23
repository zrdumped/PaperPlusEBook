#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H
#include <book.h>
#include <map>
#include <QString>
#include <QImage>
#include <vector>

class BookManager
{
public:
    BookManager();
    std::vector<Book*> getAllBooks();
    std::vector<Note> getAllNotes();
    int addNote(QString name, QString intro);
    int addBook(QString filepath, QString name);
    void selectNote(QString name);
    QString getBookPageWithPageNumber(int p);
    QImage getNotePageWithPageNumber(int p);
    QString getBookName();
    QString getNoteName();
    void switchBook(QString name);
    Book* getSingleBook(QString name);
    Note getSingleNote(QString name);
    void openBook();
    void closeBook();
    QString fetchLastReadFromBook(QString bookname, int p);
    void setLastRead(int p);
    int getLastRead();
    int getPageCount();
    void storeNotePage(QImage &img, int p);
private:
    std::map<QString, Book*> bookMap;
    QString currentBook = "";
};

#endif // BOOKMANAGER_H

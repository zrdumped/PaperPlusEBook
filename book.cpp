#include "book.h"

Book::Book()
{

}

int Book::CreateNewBook(QString bookPath, QString bookName){
    QDir workDir;
    QDir bookDir(bookName);
    if(bookDir.exists())
        return -1;
    int r = workDir.mkdir(bookName);
    if(!r)
        return -2;
    QString bookFileName = QFile(bookPath).fileName();
    QString newBookPath = bookDir.absoluteFilePath(bookFileName);
    QFile::copy(bookPath, newBookPath);
    meta.setBookPath(bookPath);
    meta.setBookPageCount(TxtParser::ParseFile(newBookPath, pagemeta.getPageDataFileName(newBookPath)));
    meta.setLastReadPage(0);
    meta.setLastReadTime(QFileInfo(newBookPath).lastRead());
    meta.storeMeta();
    return 0;
}

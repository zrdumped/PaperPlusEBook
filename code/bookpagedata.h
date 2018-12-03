#ifndef BOOKPAGEDATA_H
#define BOOKPAGEDATA_H
#include <fstream>
#include <QString>

class BookPagedata
{
/*
 * The file name of metadata looks like this: bookName.bookpage
 * file format: end of page 0 | end of page 1 |......
 *                  4 bytes      |      4 bytes     |......
 */
public:
    BookPagedata();
    unsigned int page2Offset(int p);
    bool load(QString bookPath);
    void unload();
    QString getPageDataFileName(QString bookPath);

private:
    std::ifstream pagedataFile;
    QString extension = ".bookpage";
};

#endif // BOOKPAGEDATA_H

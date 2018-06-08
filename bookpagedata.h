#ifndef BOOKPAGEDATA_H
#define BOOKPAGEDATA_H
#include <fstream>
#include <QString>

class BookPagedata
{
/*
 * The file name of metadata looks like this: bookName.bookpage
 * file format: offset of page 0 | offset of page 1 |......
 *                  4 bytes      |      4 bytes     |......
 */
public:
    BookPagedata();
    BookPagedata(QString bookPath);
    unsigned int page2Offset(unsigned int p);
    bool load(QString bookPath);
    ~BookPagedata();
private:
    std::ifstream pagedataFile;
    QString extension = ".bookpage";
};

#endif // BOOKPAGEDATA_H

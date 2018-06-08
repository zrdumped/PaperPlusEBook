#include "bookpagedata.h"
#include <txtparser.h>
#include <QFileInfo>
#include <QDir>
BookPagedata::BookPagedata()
{

}

BookPagedata::~BookPagedata()
{
    pagedataFile.close();
}

BookPagedata::BookPagedata(QString bookPath){
    QFileInfo f(bookPath);
    QString path = f.absoluteDir().absolutePath() + '/' + f.fileName().split('.')[0] + extension;
    pagedataFile.open(path.toLocal8Bit().toStdString().c_str(), std::fstream::in);
}

unsigned int BookPagedata::page2Offset(unsigned int p){
    pagedataFile.seekg(4 * p, std::ios_base::beg);
    TxtParser::charandint ci;
    ci.i = 0;
    pagedataFile.read(ci.c, 4);
    return ci.i;
}

bool BookPagedata::load(QString bookPath){
    QFileInfo f(bookPath);
    QString path = f.absoluteDir().absolutePath() + '/' + f.fileName().split('.')[0] + extension;
    pagedataFile.open(path.toLocal8Bit().toStdString().c_str(), std::fstream::in);
    return pagedataFile.is_open();
}

#include "bookpagedata.h"
#include <txtparser.h>
#include <QFileInfo>
#include <QDir>
#include <iostream>
#include <QCoreApplication>
BookPagedata::BookPagedata()
{

}

unsigned int BookPagedata::page2Offset(int p){
    if(p < 0)
        return 0;
    pagedataFile.clear();
    pagedataFile.seekg(4 * p, std::ios_base::beg);
    charandint ci;
    ci.i = 0;
    //std::cout<<pagedataFile.tellg()<<std::endl;
    pagedataFile.read(ci.c, 4);
    return ci.i;
}

bool BookPagedata::load(QString bookPath){
    unload();
    QDir workDir(QCoreApplication::applicationDirPath());

    QFileInfo f(workDir.absoluteFilePath(bookPath));
    QString path = f.absoluteFilePath() + '/' + f.fileName() + extension;
    pagedataFile.open(path.toLocal8Bit().toStdString().c_str(), std::fstream::in);
    return pagedataFile.is_open();
}

void BookPagedata::unload(){
    if(pagedataFile.is_open())
        pagedataFile.close();
}

QString BookPagedata::getPageDataFileName(QString bookPath){
     QFileInfo f(bookPath);
     return f.absoluteDir().absolutePath() + '/' + f.fileName().split("."+f.suffix())[0] + extension;
}

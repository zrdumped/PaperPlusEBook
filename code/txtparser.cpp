#include "txtparser.h"
#include <myifstream.h>
#include <iostream>
TxtParser::TxtParser()
{

}

/*
 * Ascii: 1 byte
 * GBK: 2 byte, with the first byte having a value higher than 127
 * UTF-16: 2 byte
 * UTF-16-Big-Endian: 2 byte, big endian version of utf-16
 * UTF-8: 1 to 6 bytes
*/
int TxtParser::ParseFile(QString filename, QString metafilename, int charPerLine, int linePerPage)
{
    std::string fname = filename.toLocal8Bit().toStdString();
    std::string metaname = metafilename.toLocal8Bit().toStdString();
    MyIfstream sourceFile(fname.c_str());
    if(!sourceFile.is_open()){
        return 0;
    }
    std::ofstream metaFile(metaname.c_str(), std::fstream::out | std::fstream::trunc);
    QChar c;
    int charPerLineCounter = 0;
    int linePerPageCounter = 0;
    int lastWordPos = 0;
    int pageCounter = 0;
    charandint ci;
    while(sourceFile.read(&c, 1)){
        //std::cout<<"c: "<<QString(c).toStdString()<<" pos: "<<sourceFile.tellg()<<std::endl;
        //if '\n', add a new line
        if(c == '\n'){
            linePerPageCounter ++;
            if(linePerPageCounter == linePerPage){
                linePerPageCounter = 0;
                metaFile.seekp(pageCounter * 4, std::ios_base::beg);
                ci.i = sourceFile.tellg();
                metaFile.write(ci.c, 4);
                pageCounter ++;
                //std::cout<<"page"<<pageCounter<<" ok(\\n) offset: "<<ci.i<<std::endl;
            }
        }
        //if c is ' ', update the position of the last word we met
        else if(c.isSpace()){
            lastWordPos = sourceFile.tellg();
            charPerLineCounter ++;
            if(charPerLineCounter == charPerLine){
                charPerLineCounter = 0;
                linePerPageCounter ++;
            }
            if(linePerPageCounter == linePerPage){
                linePerPageCounter = 0;
                metaFile.seekp(pageCounter * 4, std::ios_base::beg);
                ci.i = sourceFile.tellg();
                metaFile.write(ci.c, 4);
                pageCounter ++;
                //std::cout<<"page"<<pageCounter<<" ok(' ') offset: "<<ci.i<<std::endl;
            }
        }
        else if(c.isPunct()){
            //if a punctuation is the front of a line, the last word in the last line should be moved to the current line
            if(charPerLineCounter == 0){
                //if cross pages, change the position of last page
                if(linePerPageCounter == 0){
                    metaFile.seekp(pageCounter * 4 - 4, std::ios_base::beg);
                    ci.i = lastWordPos;
                    metaFile.write(ci.c, 4);
                    charPerLineCounter += sourceFile.tellg() - lastWordPos;
                }
                else {
                    charPerLineCounter += sourceFile.tellg() - lastWordPos;
                }
                if(c != '-')
                    lastWordPos = sourceFile.tellg();
            }
            else{
                charPerLineCounter ++;
                if(charPerLineCounter == charPerLine){
                    charPerLineCounter = 0;
                    linePerPageCounter ++;
                }
                if(linePerPageCounter == linePerPage){
                    linePerPageCounter = 0;
                    metaFile.seekp(pageCounter * 4, std::ios_base::beg);
                    ci.i = sourceFile.tellg();
                    metaFile.write(ci.c, 4);
                    pageCounter ++;
                    //std::cout<<"page"<<pageCounter<<" ok('punc') offset: "<<ci.i<<std::endl;
                }
            }
        }
        //english word characters
        else if(c.isLetter()){
            charPerLineCounter ++;
            if(charPerLineCounter == charPerLine){
                charPerLineCounter = 0;
                charPerLineCounter += sourceFile.tellg() - lastWordPos;
                linePerPageCounter ++;
            }
            if(linePerPageCounter == linePerPage){
                linePerPageCounter = 0;
                metaFile.seekp(pageCounter * 4, std::ios_base::beg);
                ci.i = lastWordPos;
                metaFile.write(ci.c, 4);
                pageCounter ++;
                //std::cout<<"page"<<pageCounter<<" ok(other) offset: "<<ci.i<<std::endl;
            }
        }
        //normal characters
        else {
            charPerLineCounter ++;
            if(charPerLineCounter == charPerLine){
                charPerLineCounter = 0;
                linePerPageCounter ++;
            }
            if(linePerPageCounter == linePerPage){
                linePerPageCounter = 0;
                metaFile.seekp(pageCounter * 4, std::ios_base::beg);
                ci.i = lastWordPos;
                metaFile.write(ci.c, 4);
                pageCounter ++;
                //std::cout<<"page"<<pageCounter<<" ok(other) offset: "<<ci.i<<std::endl;
            }
        }
    }
    if(charPerLineCounter + linePerPageCounter > 0){
        metaFile.seekp(pageCounter * 4, std::ios_base::beg);
        ci.i = sourceFile.tellg();
        metaFile.write(ci.c, 4);
        pageCounter ++;
        //std::cout<<"page"<<pageCounter<<" ok(rest) offset: "<<ci.i<<std::endl;
    }
    metaFile.seekp(pageCounter * 4, std::ios_base::beg);
    sourceFile.clear();
    ci.i = sourceFile.tellend();
    metaFile.write(ci.c, 4);
    sourceFile.close();
    metaFile.flush();
    metaFile.close();
    return pageCounter;
}


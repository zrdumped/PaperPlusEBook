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
    std::ofstream metaFile(metaname.c_str(), std::fstream::out | std::fstream::trunc);
    QChar c;
    int charPerLineCounter = 0;
    int linePerPageCounter = 0;
    int lastWordPos = 0;
    int pageCounter = 0;
    charandint ci;
    while(sourceFile.read(&c, 1)){
        //if '\n', add a new line
        if(c == '\n'){
            linePerPageCounter ++;
            if(linePerPageCounter == linePerPage){
                linePerPageCounter = 0;
                metaFile.seekp(pageCounter * 4, std::ios_base::beg);
                ci.i = sourceFile.tellg();
                metaFile.write(ci.c, 4);
                pageCounter ++;
            }
        }
        //if c is ' ', update the position of the last word we met
        else if(c == ' '){
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
            }
        }
        else if(CheckPunctuation(c)){
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
                }
            }
        }
        //normal characters
        else {
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
            }
        }
    }
    if(charPerLineCounter + linePerPageCounter > 0){
        metaFile.seekp(pageCounter * 4, std::ios_base::beg);
        ci.i = sourceFile.tellg();
        metaFile.write(ci.c, 4);
        pageCounter ++;
    }
    sourceFile.close();
    metaFile.flush();
    metaFile.close();
    return pageCounter;
}

bool TxtParser::CheckPunctuation(QChar qc){
    char c = qc.toLatin1();
    return (c > 32 && c < 48) || (c > 57 && c < 65) || (c > 90 && c < 97) || (c > 123 && c < 125);
}


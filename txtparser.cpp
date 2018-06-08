#include "txtparser.h"
#include <fstream>
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
void TxtParser::ParseFile(QString filename, QString metafilename, int charPerLine, int linePerPage)
{
    /*FileCode code = CheckFileCode(filename);
    std::string fname = filename.toLocal8Bit().toStdString();
    std::string metaname = metafilename.toLocal8Bit().toStdString();
    std::ifstream sourceFile(fname.c_str());
    std::ofstream metaFile(metaname.c_str());
    char c;
    wchar_t wc;
    int charPerLineCounter = 0;
    int linePerPageCounter = 0;
    int lastWordPos = 0;
    int pageCounter = 0;
    charandint ci;
    switch (code) {
    case UTF_16:
    case UTF_16_BIG_ENDIAN:
    case UTF_8:

        break;
    case ANSI:
        while(sourceFile.read(&c, 1)){
            //if '\n', add a new line
            if(c == '\n'){
                linePerPageCounter ++;
                if(linePerPageCounter == linePerPage){
                    linePerPageCounter = 0;
                    metaFile.seekp(pageCounter * 4, std::ios_base::beg);
                    ci.i = sourceFile.tellg();
                    metaFile.write(ci.c, 4);
                    pageCounter;
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

                }
            }
            else {

            }
        }
    default:
        break;
    }
    std::cout<<code<<std::endl;
    sourceFile.close();
    metaFile.flush();
    metaFile.close();*/
}

TxtParser::FileCode TxtParser::CheckFileCode(QString filename)
{
    std::string fname = filename.toLocal8Bit().toStdString();
    std::ifstream fin(fname.c_str(), std::ios::binary);
    unsigned char s2;
    fin.read((char*)&s2, sizeof(s2));
    int p = s2<<8;
    fin.read((char*)&s2, sizeof(s2));
    p +=s2;
    FileCode code;
    switch(p)//判断文本前两个字节
    {
    case 0xfffe:
        code = UTF_16;
        break;
    case 0xfeff:
        code = UTF_16_BIG_ENDIAN;
        break;
    case 0xefbb:
        code = UTF_8;
        break;
 default:
        code = ANSI;
     }
     fin.close();
     return code;
}

bool TxtParser::CheckPunctuation(char c){
    return (c > 32 && c < 48) || (c > 57 && c < 65) || (c > 90 && c < 97) || (c > 123 && c < 125);
}


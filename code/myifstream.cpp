#include "myifstream.h"
#include <QTextCodec>
#include <iostream>
MyIfstream::MyIfstream()
{
    f = std::ifstream();
}

MyIfstream::MyIfstream(const char *fname)
{
    f.open(fname, std::fstream::in);
    setCodetype();
}

bool MyIfstream::eof(){
    return f.eof();
}

void MyIfstream::open(const char *fname){
    f.open(fname, std::fstream::in);
    setCodetype();
}

unsigned int MyIfstream::tellg(){
    return f.tellg();
}

void MyIfstream::seekg(unsigned int pos){
    f.seekg(pos, std::ios_base::beg);
}

void MyIfstream::clear(){
    f.clear();
}

unsigned int MyIfstream::tellend(){
    f.seekg(0, std::ios_base::end);
    return f.tellg();
}

void MyIfstream::setCodetype(){
    unsigned char s2;
    f.read((char*)&s2, sizeof(s2));
    int p = s2<<8;
    f.read((char*)&s2, sizeof(s2));
    p += s2;
    switch(p)//判断文本前两个字节
    {
    case 0xfffe:
        codeType = UTF_16;
        break;
    case 0xfeff:
        codeType = UTF_16_BIG_ENDIAN;
        break;
    case 0xefbb:
        codeType = UTF_8;
        break;
 default:
        codeType = ANSI;
     }
}

QChar MyIfstream::getCharWithDecoded(){
    switch (codeType) {
    case UTF_16:
        return getUTF_16();
        break;
    case UTF_16_BIG_ENDIAN:
        return getUTF_16_BIG_ENDIAN();
        break;
    case UTF_8:
        return getUTF_8();
        break;
    case ANSI:
        return getANSI();
        break;
    default:
        break;
    }
}

QChar MyIfstream::getUTF_16(){
    char c = 0;
    ushort wc = 0;
    f.read(&c, 1);
    uchar uc = c;
    wc += uc;
    wc <<= 8;
    f.read(&c, 1);
    uc = c;
    wc += uc;
    QString p = QString::fromUtf16(&wc,1);
    return p[0];
}

QChar MyIfstream::getUTF_8(){
    std::string t = "";
    char h = 0, c = 0;
    int len = 0;
    f.read(&h, 1);
    t += h;
    len ++;
    if(h & 0x80)
        h <<= 1;
    while(h & 0x80){
        h <<= 1;
        f.read(&c, 1);
        t += c;
        len ++;
    }
    QString p = QString::fromUtf8(t.c_str(), len);
    return p[0];
}

QChar MyIfstream::getUTF_16_BIG_ENDIAN(){
    char c = 0;
    ushort wc = 0, wctmp = 0;
    uchar uc = 0;
    f.read(&c, 1);
    uc = c;
    wc += uc;
    f.read(&c, 1);
    uc = c;
    wctmp = uc << 8;
    wc += wctmp;
    QString p = QString::fromUtf16(&wc,1);
    return p[0];
}

QChar MyIfstream::getANSI(){
    char c = 0;
    uchar uc = 0;
    QString a = "";
    f.read(&c, 1);
    uc = c;
    a += uc;
    if(c > 127){
        f.read(&c, 1);
        uc = c;
        a += uc;
    }
    QString text = QTextCodec::codecForName("GB18030")->toUnicode(a.toLatin1());
    return text[0];
}

void MyIfstream::close(){
    f.close();
}

int MyIfstream::read(QChar *c, int size){
    if(f.eof())
        return 0;
    for(int i = 0; i < size; i++){
        c[i] = getCharWithDecoded();
        if(f.eof())
            return i + 1;
    }
    return size;
}

QString MyIfstream::readsome(int charSize){
    std::cout<<"get here!!!"<<charSize<<std::endl;
    if(f.eof())
        return "";
    QString s = "";
    std::cout<<"get here!!!!!"<<std::endl;
    for(int i = 0; i < charSize; i++){
        s += getCharWithDecoded();
    }
    std::cout<<"get here!!!!"<<std::endl;
    return s;
}

bool MyIfstream::is_open(){
    return f.is_open();
}

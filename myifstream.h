#ifndef MYIFSTREAM_H
#define MYIFSTREAM_H
#include <QString>
#include <fstream>

class MyIfstream
{
public:
    enum FileCode{
        ANSI = 0, UTF_16, UTF_8, UTF_16_BIG_ENDIAN
    };
    MyIfstream();
    MyIfstream(const char *fname);
    bool eof();
    void open(const char *fname);
    void close();
    unsigned int tellg();
    void seekg(unsigned int pos);
    QChar getCharWithDecoded();
    int read(QChar *c, int size);
private:
    std::ifstream f;
    FileCode codeType;
    void setCodetype();
    QChar getUTF_16();
    QChar getUTF_8();
    QChar getUTF_16_BIG_ENDIAN();
    QChar getANSI();
};

#endif // MYIFSTREAM_H

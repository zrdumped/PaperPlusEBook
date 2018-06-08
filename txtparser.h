#ifndef TXTPARSER_H
#define TXTPARSER_H
#include <QString>

class TxtParser
{
public:
    union charandint{
        int i;
        char c[4];
    };
    enum FileCode{
        ANSI = 0, UTF_16, UTF_8, UTF_16_BIG_ENDIAN
    };
    TxtParser();
    static void ParseFile(QString filename, QString metafilename, int charPerLine, int linePerPage);
    static FileCode CheckFileCode(QString filename);
    static bool CheckPunctuation(char c);
};

#endif // TXTPARSER_H

#ifndef TXTPARSER_H
#define TXTPARSER_H
#include <QString>
union charandint{
    int i;
    char c[4];
};
class TxtParser
{
public:
    enum FileCode{
        ANSI = 0, UTF_16, UTF_8, UTF_16_BIG_ENDIAN
    };
    TxtParser();
    static int ParseFile(QString filename, QString metafilename, int charPerLine = 40, int linePerPage = 40);
    static bool CheckPunctuation(QChar c);
};

#endif // TXTPARSER_H

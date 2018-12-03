#ifndef NOTEMETADATA_H
#define NOTEMETADATA_H
#include <QString>
#include <QDateTime>

class NoteMetadata
{
/* The file name of metadata looks like this: noteName.notemeta
 * file format: length of introduction |  introduction
 *                      4 bytes        |  length bytes
 * Properties:
 * introduction: the introduction of the note
 */
public:
    NoteMetadata();
    NoteMetadata(QString notepath);
    bool loadMeta(QString notepath);
    QDateTime getLastModifiedTime();
    void setLastModifiedTime(QDateTime dt);
    QString getIntroduction();
    void setIntroduction(QString intro);
    void setNotePath();
    void storeMeta();
private:
    QString notePath;
    QString introduction;
    QDateTime lastModifiedTime;
    QString extension = ".notemeta";
};

#endif // NOTEMETADATA_H

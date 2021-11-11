#ifndef IFILEWRITER_H
#define IFILEWRITER_H
#include <QDataStream>
#include <QFile>
#include <qfuture.h>
#include <qstring.h>
template<typename TDataFormat>
class IFileWriter
{
public:
    virtual QFuture<bool> save(const TDataFormat &data) const = 0;
    virtual void setFileName(const QString &fileName) = 0;
};
#endif // IFILEWRITER_H

#ifndef IFILEREADER_H
#define IFILEREADER_H

#include <qdatastream.h>
#include <qfile.h>
#include <qfuture.h>
#include <qstring.h>
template<typename TDataFormat>
class IFileReader
{
public:
    virtual QFuture<TDataFormat> read() const = 0;
    virtual void setFileName(const QString &fileName) = 0;
};

#endif // IFILEREADER_H

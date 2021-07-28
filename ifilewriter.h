#ifndef IFILEWRITER_H
#define IFILEWRITER_H
#include <QDataStream>
#include <QFile>
#include <qstring.h>
template<typename TDataFormat>
class IFileWriter
{
public:
    virtual void write(const TDataFormat &data) const = 0;
};
#endif // IFILEWRITER_H

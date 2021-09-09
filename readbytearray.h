#ifndef READBYTEARRAY_H
#define READBYTEARRAY_H

#include "ifilereader.h"

class ReadByteArray : public IFileReader<QByteArray>
{
public:
    ReadByteArray(const QString &fileName):
        _fileName(fileName){}
    virtual QByteArray read() const
    {
        QFile file(_fileName);
        if(!file.exists())
            return QByteArray();
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        QByteArray obj;
        in >> obj;
        return obj;
    }
private:
    const QString _fileName;
};

#endif // READBYTEARRAY_H

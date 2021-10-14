#ifndef READBYTEARRAY_H
#define READBYTEARRAY_H

#include "FileOperationsContext/SLAs/ifilereader.h"

class ReadByteArray : public IFileReader<QByteArray>
{
public:
    QByteArray read() const override
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
    void setFileName(const QString &fileName) override
    {
        _fileName = fileName;
    }
private:
    QString _fileName;
};

#endif // READBYTEARRAY_H

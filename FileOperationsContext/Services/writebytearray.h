#ifndef WRITEBYTEARRAY_H
#define WRITEBYTEARRAY_H

#include "FileOperationsContext/SLAs/ifilewriter.h"
class WriteByteArray : public IFileWriter<QByteArray>
{
public:
    void write(const QByteArray &byteArray) const override
    {
        QFile file(_fileName);
        if(!file.open(QIODevice::WriteOnly))
            throw "File readings issues: Can't write to file. Maybe it's non existent or access issues";
        QDataStream out(&file);
        out << byteArray;
        file.close();
    }
    virtual void setFileName(const QString &fileName) override
    {
        _fileName = fileName;
    }
private:
    QString _fileName;
};

#endif // BYTESFILEWRITER_H

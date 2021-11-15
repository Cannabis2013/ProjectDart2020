#ifndef WRITEBYTEARRAY_H
#define WRITEBYTEARRAY_H

#include "FileOperationsContext/SLAs/ifilewriter.h"
#include <QtConcurrent/QtConcurrent>
class WriteByteArray : public IFileWriter<QByteArray>
{
public:
    QFuture<bool> saveAsync(const QByteArray &byteArray) const override
    {
        return QtConcurrent::run([=]{
            QFile file(_fileName);
            if(!file.open(QIODevice::WriteOnly))
                throw "File readings issues: Can't write to file. Maybe it's non existent or access issues";
            QDataStream out(&file);
            out << byteArray;
            file.close();
            return true;
        });
    }
    virtual void setFileName(const QString &fileName) override
    {
        _fileName = fileName;
    }
private:
    QString _fileName;
};

#endif // BYTESFILEWRITER_H

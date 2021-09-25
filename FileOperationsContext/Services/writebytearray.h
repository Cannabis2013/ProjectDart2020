#ifndef WRITEBYTEARRAY_H
#define WRITEBYTEARRAY_H

#include "FileOperationsContext/SLAs/ifilewriter.h"
class WriteByteArray : public IFileWriter<QByteArray>
{
public:
    WriteByteArray(const QString &fileName): _fileName(fileName){}
    void write(const QByteArray &byteArray) const
    {
        QFile file(_fileName);
        if(!file.open(QIODevice::WriteOnly))
            throw "File readings issues: Can't write to file. Maybe it's non existent or access issues";
        QDataStream out(&file);
        out << byteArray;
        file.close();
    }
private:
    const QString _fileName;
};

#endif // BYTESFILEWRITER_H

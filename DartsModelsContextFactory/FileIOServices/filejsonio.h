#ifndef FILEJSONIO_H
#define FILEJSONIO_H
#include "FileIOSLAs/ifiledataio.h"
class FileJsonIO : public IFileDataIO<QByteArray>
{
public:
    FileJsonIO(const QString &fileName)
    {
        _fileName = fileName;
    }
    Data read() override
    {
        QFile file(_fileName);
        if(!file.exists())
            return QByteArray();
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        QByteArray byteArray;
        in >> byteArray;
        return byteArray;
    }
    bool save(const Data &byteArray) override
    {
        QFile file(_fileName);
        if(!file.open(QIODevice::WriteOnly))
            return false;
        QDataStream out(&file);
        out << byteArray;
        file.close();
        return true;
    }
private:
    QString _fileName;
};
#endif // READBYTEARRAY_H

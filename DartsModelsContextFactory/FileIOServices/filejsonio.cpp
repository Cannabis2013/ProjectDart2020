#include "filejsonio.h"

FileJsonIO::FileJsonIO(const QString &fileName):
    _fileName(fileName){}

IFileDataIO::Data FileJsonIO::read()
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


bool FileJsonIO::save(const Data &byteArray)
{
    QFile file(_fileName);
    if(!file.open(QIODevice::WriteOnly))
        return false;
    QDataStream out(&file);
    out << byteArray;
    file.close();
    return true;
}

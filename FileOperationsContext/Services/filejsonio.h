#ifndef FILEJSONIO_H
#define FILEJSONIO_H
#include "FileOperationsContext/SLAs/ifiledataio.h"
#include <QtConcurrent/QtConcurrent>
#include <qmutex.h>
#include <QMutexLocker>
class FileJsonIO : public IFileDataIO<QByteArray>
{
public:
    FileJsonIO(const QString &fileName)
    {
        _fileName = fileName;
    }
    Data read() override
    {
        QMutexLocker locker(&_mutex);
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
        QMutexLocker locker(&_mutex);
        QFile file(_fileName);
        if(!file.open(QIODevice::WriteOnly))
            return false;
        QDataStream out(&file);
        out << byteArray;
        file.close();
        return true;
    }
private:
    QMutex _mutex;
    QString _fileName;
};
#endif // READBYTEARRAY_H

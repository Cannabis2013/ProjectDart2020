#include "filejsonio.h"

#include <QDataStream>

FileJsonIO::FileJsonIO(const QString &fileName):
        _fileName(fileName){}

QByteArray FileJsonIO::read()
{
        auto file = openFile(_fileName, QIODevice::ReadOnly);
        if (!file)
                return QByteArray();
        return readJson(file);
}

bool FileJsonIO::write(const QByteArray& json)
{
        auto file = openFile(_fileName, QIODevice::WriteOnly);
        return writeJson(file, json);
}

QFile* FileJsonIO::openFile(const QString& filename, const QIODevice::OpenMode& mode)
{
        QFile* file = new QFile(filename);
        file->open(mode);
        return file;
}

QByteArray FileJsonIO::readJson(QFile* const file)
{
        QDataStream in(file);
        QByteArray byteArray;
        in >> byteArray;
        file->close();
        return byteArray;
}

bool FileJsonIO::writeJson(QFile* const file, const QByteArray& json)
{
        QDataStream out(file);
        out << json;
        file->close();
        return true;
}

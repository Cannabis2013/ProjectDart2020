#include "filejsonio.h"

#include <QDataStream>
#include <QJsonDocument>

FileJsonIO::FileJsonIO(const QString &fileName):
    _fileName(fileName){}

QByteArray FileJsonIO::read() const
{
    auto file = openFile(_fileName, QIODevice::ReadOnly);
    if (!file)
        return QByteArray();
    return readJson(file);
}

QJsonDocument FileJsonIO::readAsJson() const
{
    auto file = openFile(_fileName, QIODevice::ReadOnly);
    if (!file)
        return QJsonDocument();
    auto byteArray = readJson(file);
    return QJsonDocument::fromJson(byteArray);
}

bool FileJsonIO::write(const QByteArray& json)
{
    auto file = openFile(_fileName, QIODevice::WriteOnly);
    return writeJson(file, json);
}

bool FileJsonIO::write(const QJsonArray& arr)
{
    auto file = openFile(_fileName, QIODevice::WriteOnly);
    auto json = QJsonDocument(arr).toJson(QJsonDocument::Compact);
    return writeJson(file, json);
}

bool FileJsonIO::write(const QJsonObject& obj)
{
    auto file = openFile(_fileName, QIODevice::WriteOnly);
    auto json = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    return writeJson(file, json);
}

QFile *FileJsonIO::openFile(const QString &filename, const QIODevice::OpenMode &mode) const
{
    QFile* file = new QFile(filename);
    return file->open(mode) ? file : NULL;
}

QByteArray FileJsonIO::readJson(QFile *const file) const
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

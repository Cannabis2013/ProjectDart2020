#include "filejsonio.h"

#include <QDataStream>
#include <QJsonDocument>

FileJsonIO::FileJsonIO(const QString &fileName):
        _fileName(fileName){}

QByteArray FileJsonIO::read()
{
        auto file = openFile(_fileName, QIODevice::ReadOnly);
        if (!file)
                return QByteArray();
        return readJson(file);
}

QJsonDocument FileJsonIO::readAsJson()
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

bool FileJsonIO::writeAsJson(const QJsonArray& arr)
{
        auto file = openFile(_fileName, QIODevice::WriteOnly);
        auto json = QJsonDocument(arr).toJson(QJsonDocument::Compact);
        return writeJson(file, json);
}

bool FileJsonIO::writeAsJson(const QJsonObject& obj)
{
        auto file = openFile(_fileName, QIODevice::WriteOnly);
        auto json = QJsonDocument(obj).toJson(QJsonDocument::Compact);
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

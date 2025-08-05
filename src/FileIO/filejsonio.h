#ifndef FILEJSONIO_H
#define FILEJSONIO_H

#include <qbytearray.h>
#include <qfile.h>

class FileJsonIO
{
public:
    FileJsonIO(const QString& fileName);
    QByteArray read() const;
    QJsonDocument readAsJson() const;
    bool write(const QByteArray& json);
    bool write(const QJsonArray& arr);
    bool write(const QJsonObject& obj);

private:
        // Class member methods
        QFile* openFile(const QString& filename, const QIODevice::OpenMode& mode) const;
        QByteArray readJson(QFile* const file) const;
        bool writeJson(QFile* const file, const QByteArray& json);

        // Class member variable
        const QString _fileName;
};

#endif // READBYTEARRAY_H

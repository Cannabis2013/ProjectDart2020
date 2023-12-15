#ifndef FILEJSONIO_H
#define FILEJSONIO_H

#include <qbytearray.h>
#include <qfile.h>

class FileJsonIO
{
public:
        FileJsonIO(const QString& fileName);
        QByteArray read();
        bool write(const QByteArray& json);

private:
        // Class member methods
        QFile* openFile(const QString& filename, const QIODevice::OpenMode& mode);
        QByteArray readJson(QFile* const file);
        bool writeJson(QFile* const file, const QByteArray& json);

        // Class member variable
        const QString _fileName;
};

#endif // READBYTEARRAY_H

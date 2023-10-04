#ifndef FILEJSONIO_H
#define FILEJSONIO_H

#include <qbytearray.h>
#include <qdatastream.h>
#include <qfile.h>

class FileJsonIO
{
public:
    FileJsonIO(const QString &fileName);
    QByteArray read();
    bool write(const QByteArray &byteArray);

private:
    const QString _fileName;
};

#endif // READBYTEARRAY_H

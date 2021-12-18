#ifndef FILEJSONIO_H
#define FILEJSONIO_H
#include "IOSLAs/ifiledataio.h"
#include <qstring.h>
class QByteArray;
class FileJsonIO : public IFileDataIO<QByteArray>
{
public:
    FileJsonIO(const QString &fileName);
    Data read() override;
    bool save(const Data &byteArray) override;
private:
    QString _fileName;
};
#endif // READBYTEARRAY_H

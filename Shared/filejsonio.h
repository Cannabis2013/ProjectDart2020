#ifndef FILEJSONIO_H
#define FILEJSONIO_H

#include <qbytearray.h>
#include <qdatastream.h>
#include <qfile.h>
#include <DartsModelsContext/Contracts/Db/ifiledataio.h>

class FileJsonIO : public IFileDataIO
{
public:
    FileJsonIO(const QString &fileName);
    virtual Data read() override;
    virtual bool save(const Data &byteArray) override;
private:
    const QString _fileName;
};

#endif // READBYTEARRAY_H

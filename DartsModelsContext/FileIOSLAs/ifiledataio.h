#ifndef IFILEDATAIO_H
#define IFILEDATAIO_H

class QString;
class QByteArray;

class IFileDataIO
{
public:
    typedef QByteArray Data;
    virtual Data read() = 0;
    virtual bool save(const Data &data) = 0;
};

#endif // IFILEREADER_H

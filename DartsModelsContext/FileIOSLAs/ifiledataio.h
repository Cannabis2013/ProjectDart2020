#ifndef IFILEDATAIO_H
#define IFILEDATAIO_H
#include <qdatastream.h>
#include <qfile.h>
#include <qfuture.h>
#include <qstring.h>
template<typename TData>
class IFileDataIO
{
public:
    typedef TData Data;
    virtual Data read() = 0;
    virtual bool save(const Data &data) = 0;
};

#endif // IFILEREADER_H

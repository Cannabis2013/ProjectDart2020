#ifndef IFILEDATAIO_H
#define IFILEDATAIO_H
template<typename TData>
class IFileDataIO
{
public:
    typedef TData Data;
    virtual Data read() = 0;
    virtual bool save(const Data &data) = 0;
};

#endif // IFILEREADER_H

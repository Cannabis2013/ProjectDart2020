#ifndef ABSTRACTLOADFROMSTORAGE_H
#define ABSTRACTLOADFROMSTORAGE_H
#include "icreatemodelsfrom.h"
#include "idbcontext.h"
#include "FileOperationsContext/SLAs/ifiledataio.h"
template<typename TModel,typename TData>
class AbstractLoadFromStorage
{
public:
    typedef TModel Model;
    typedef TData Data;
    typedef ICreateModelsFrom<Data,Model> Converter;
    typedef IDbContext<Model> DbContext;
    virtual bool load(DbContext *dbCtx, Converter *converter) const = 0;
protected:
    void setIoDevice(IFileDataIO<Data> *device)
    {
        _ioDevice = device;
    }
    IFileDataIO<Data> *ioDevice() const
    {
        return _ioDevice;
    }
private:
    IFileDataIO<Data> *_ioDevice;
};
#endif // IFETCHMEMDB_H

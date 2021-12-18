#ifndef ABSTRACTLOADFROMSTORAGE_H
#define ABSTRACTLOADFROMSTORAGE_H
#include "iconverttomodels.h"
#include "DbSLAs/idbcontext.h"
#include "FileIOSLAs/ifiledataio.h"
template<typename TModel,typename TData>
class AbstractLoadModels
{
public:
    typedef TModel Model;
    typedef TData Data;
    typedef IConvertToModels<Data,Model> Converter;
    typedef IDbContext<Model> DbCtx;
    virtual bool load(DbCtx *dbCtx, Converter *converter) const = 0;
protected:
    void setIoDevice(IFileDataIO<Data> *device) {_ioDevice = device;}
    IFileDataIO<Data> *ioDevice() const {return _ioDevice;}
private:
    IFileDataIO<Data> *_ioDevice;
};
#endif // IFETCHMEMDB_H

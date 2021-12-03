#ifndef ABSTRACTSAVETOSTORAGE_H
#define ABSTRACTSAVETOSTORAGE_H
#include "icreatedatafrom.h"
#include "idbcontext.h"
#include <qfuture.h>
#include <quuid.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
#include "FileOperationsContext/SLAs/ifiledataio.h"
template<typename TModel, typename TData>
class AbstractSaveToStorage
{
public:
    typedef TModel Model;
    typedef TData Data;
    typedef IDbContext<Model> DbContext;
    typedef ICreateDataFrom<Model,Data> Converter;
    struct ServiceProvider
    {
        DbContext *dbContext;
        Converter *converter;
    };
    virtual bool save(DbContext *dbCtx, Converter *converter)  = 0;
    virtual bool save(const std::initializer_list<ServiceProvider> &list) = 0;
    IFileDataIO<Data> *ioDevice() const{return _ioDevice;};
    void setIoDevice(IFileDataIO<Data> *newIoDevice) {_ioDevice = newIoDevice;}
private:
    IFileDataIO<Data> *_ioDevice;
};
#endif // IPERSISTMODELS_H

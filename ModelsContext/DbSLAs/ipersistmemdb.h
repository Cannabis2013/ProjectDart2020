#ifndef IPERSISTMEMDB_H
#define IPERSISTMEMDB_H
#include "icreatedatafrom.h"
#include "idbcontext.h"
#include <qfuture.h>
#include <quuid.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
#include "FileOperationsContext/SLAs/ifiledataio.h"
template<typename TModel, typename TData>
class IPersistMemDb
{
public:
    typedef TModel Model;
    typedef TData Data;
    typedef ICreateDataFrom<Model,Data> Converter;
    virtual bool save(IDbContext<Model> *dbCtx, Converter *converter)  = 0;
    IFileDataIO<Data> *ioDevice() const{return _ioDevice;};
    void setIoDevice(IFileDataIO<Data> *newIoDevice) {_ioDevice = newIoDevice;}
private:
    IFileDataIO<Data> *_ioDevice;
};
#endif // IPERSISTMODELS_H

#ifndef PERSISTDBCTX_H
#define PERSISTDBCTX_H
#include "ModelsContext/DbSLAs/ipersistmemdb.h"
#include <qjsonobject.h>
class SaveToStorage : public IPersistMemDb<IModel<QUuid>,QByteArray>
{
public:
    SaveToStorage(IFileDataIO<QByteArray> *ioDevice)
    {
        setIoDevice(ioDevice);
    }
    virtual bool save(IDbContext<Model> *dbCtx, Converter *converter) override
    {
        auto json = ioDevice()->read();
        auto models = dbCtx->models();
        converter->create(models,json);
        return ioDevice()->save(json);
    }
};
#endif // PERSISTDBCTX_H

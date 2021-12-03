#ifndef PERSISTDBCTX_H
#define PERSISTDBCTX_H
#include "ModelsContext/DbSLAs/abstractsavetostorage.h"
#include <qjsonobject.h>
class SaveToStorage : public AbstractSaveToStorage<IModel<QUuid>,QByteArray>
{
public:
    SaveToStorage(IFileDataIO<QByteArray> *ioDevice)
    {
        setIoDevice(ioDevice);
    }
    virtual bool save(IDbContext<Model> *dbContext, Converter *converter) override
    {
        return saveToStorage(dbContext,converter);
    }
    virtual bool save(const std::initializer_list<ServiceProvider> &list) override
    {
        auto result = true;
        QList<ServiceProvider> sPs(list);
        for (const auto & sP : sPs) {
            if(!saveToStorage(sP.dbContext,sP.converter))
                result = false;
        }
        return result;
    }
private:
    bool saveToStorage(DbContext *_dbCtx, Converter *_cvtr)
    {
        auto bytearray = ioDevice()->read();
        return ioDevice()->save(_cvtr->create(_dbCtx->models(),bytearray));
    }
};
#endif // PERSISTDBCTX_H

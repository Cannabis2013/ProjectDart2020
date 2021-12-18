#ifndef PERSISTDBCTX_H
#define PERSISTDBCTX_H
#include "DbSLAs/abstractsavetostorage.h"
#include <qjsonobject.h>
#include <quuid.h>
#include "ModelSLAs/imodel.h"
#include "DbSLAs/idbcontext.h"
#include "DbSLAs/imodelconverter.h"
#include "FileIOSLAs/ifiledataio.h"
class SaveToStorage : public AbstractSaveToStorage<IModel<QUuid>,QByteArray,IDbContext<IModel<QUuid>>,
                                                   IModelConverter<IModel<QUuid>,QByteArray>>
{
public:
    SaveToStorage(IODevice *ioDevice):AbstractSaveToStorage(ioDevice){}
    virtual bool save(DbCtx *dbCtx, Converter *converter) override {return _save(dbCtx,converter);}
    virtual bool save(const std::initializer_list<ServiceProvider> &list) override
    {
        auto result = true;
        QList<ServiceProvider> sPs(list);
        for (const auto & sP : sPs) {
            if(!_save(sP.dbContext,sP.converter))
                result = false;
        }
        return result;
    }
private:
    bool _save(DbCtx *_dbCtx, Converter *_cvtr)
    {
        auto bytearray = ioDevice()->read();
        return ioDevice()->save(_cvtr->create(_dbCtx->models(),bytearray));
    }
};
#endif // PERSISTDBCTX_H

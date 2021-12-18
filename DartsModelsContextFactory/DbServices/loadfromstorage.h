#ifndef LOADFROMSTORAGE_H
#define LOADFROMSTORAGE_H
#include <qjsonobject.h>
#include "ModelSLAs/imodel.h"
#include "DbSLAs/abstractloadmodels.h"
namespace LdMdCtx
{
    typedef IModel<QUuid> Model;
    typedef QByteArray Json;
    typedef IConvertToModels<Json,Model> Converter;
}
class LoadFromStorage : public AbstractLoadModels<LdMdCtx::Model,QByteArray>
{
public:
    LoadFromStorage(IFileDataIO<Data> *ioDevice)
    {
        setIoDevice(ioDevice);
    }
    bool load(DbCtx *dbCtx, Converter *cvtr) const override
    {
        auto json = ioDevice()->read();
        QVector<Model*> models = cvtr->convert(json);
        fetchDb(models,dbCtx);
        return true;
    }
private:
    void fetchDb(const QVector<Model*> &models, DbCtx *dbCtx) const
    {
        for (const auto &model : models)
            dbCtx->add(model);
    }
};
#endif // FETCHFROMSTORAGE_H

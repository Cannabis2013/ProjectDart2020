#ifndef LOADFROMSTORAGE_H
#define LOADFROMSTORAGE_H
#include <qjsonobject.h>
#include "ModelsContext/DbSLAs/abstractloadfromstorage.h"
class LoadFromStorage : public AbstractLoadFromStorage<IModel<QUuid>,QByteArray>
{
public:
    LoadFromStorage(IFileDataIO<Data> *ioDevice)
    {
        setIoDevice(ioDevice);
    }
    bool load(DbContext *dbCtx, Converter *convertFromData) const override
    {
        auto json = ioDevice()->read();
        QVector<Model*> models = convertFromData->create(json);
        fetchDb(models,dbCtx);
        return true;
    }
private:
    void fetchDb(const QVector<Model*> &models, DbContext *dbCtx) const
    {
        for (const auto &model : models)
            dbCtx->add(model);
    }
};
#endif // FETCHFROMSTORAGE_H

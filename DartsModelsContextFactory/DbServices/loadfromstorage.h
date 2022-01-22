#ifndef LOADFROMSTORAGE_H
#define LOADFROMSTORAGE_H
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <quuid.h>
#include "DbSLAs/abstractloadmodels.h"
#include "DbSLAs/iconvertfromdata.h"
#include "FileIOSLAs/ifiledataio.h"
#include "ModelSLAs/imodel.h"
class LoadFromStorage : public AbstractLoadModels<IModel<QUuid>>
{
public:
    void load(DbContext *dbContext, ModelBuilder *builder, Converter *converter, IODevice *ioDevice) const override;
};


#endif // FETCHFROMSTORAGE_H

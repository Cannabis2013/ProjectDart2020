#include "loadfromstorage.h"
#include "DbSLAs/iconvertfromdata.h"
#include "DbSLAs/idbcontext.h"

void LoadFromStorage::load(DbContext *dbContext, ModelBuilder *builder, Converter *converter, IODevice *ioDevice) const
{
    auto byteArray = ioDevice->read();
    auto models = builder->convert(byteArray,converter);
    for (const auto &model : qAsConst(models))
        dbContext->add(model);
}

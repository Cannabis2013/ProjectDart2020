#ifndef DARTSINDEXSLAS_H
#define DARTSINDEXSLAS_H
#include "iupdatedartsindexes.h"

#include "ModelsContext/ModelsSLAs/imodel.h"
class DartsIndexSLAs
{
public:
    typedef IModel<QUuid> BaseModel;
    IUpdateDartsIndexes<BaseModel> *updateIndexes() const
    {
        return _updateIndexes;
    }
    void setUpdateIndexes(IUpdateDartsIndexes<BaseModel> *updateService)
    {
        _updateIndexes = updateService;
    }
private:
    IUpdateDartsIndexes<BaseModel> *_updateIndexes;
};
#endif // DARTSINDEXSLAS_H

#ifndef DMCUTILSSLAS_H
#define DMCUTILSSLAS_H

#include "ModelsContext/MCDbSLAs/iremovemodelsfromdb.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"

class DMCUtilsSLAs
{
public:
    IRemoveModelsFromDb<IModelsDbContext> *removeModelsFromDb() const
    {
        return _removeModelsFromDb;
    }
    void setRemoveModelsFromDb(IRemoveModelsFromDb<IModelsDbContext> *service)
    {
        _removeModelsFromDb = service;
    }
private:
    IRemoveModelsFromDb<IModelsDbContext> *_removeModelsFromDb;
};

#endif // DARTSUTILITYSERVICES_H

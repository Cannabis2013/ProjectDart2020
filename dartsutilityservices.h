#ifndef DARTSUTILITYSERVICES_H
#define DARTSUTILITYSERVICES_H

#include "idbgetindexesutility.h"
#include "ModelsContext/iremovemodelsfromdb.h"
#include "ModelsContext/imodelsdbcontext.h"

class DartsUtilityServices
{
public:
    IDbGetIndexesUtility *dbGetIndexesFromjson() const;
    void setDbGetIndexesFromjson(IDbGetIndexesUtility *newDbGetIndexesFromjson);
    IRemoveModelsFromDb<IModelsDbContext> *removeModelsFromDb() const;
    void setRemoveModelsFromDb(IRemoveModelsFromDb<IModelsDbContext> *newRemoveModelFromDb);

private:
    IDbGetIndexesUtility *_dbGetIndexesFromjson;
    IRemoveModelsFromDb<IModelsDbContext> *_removeModelsFromDb;
};

#endif // DARTSUTILITYSERVICES_H

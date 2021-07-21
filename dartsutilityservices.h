#ifndef DARTSUTILITYSERVICES_H
#define DARTSUTILITYSERVICES_H

#include "idbgetindexesutility.h"
#include "iremovemodelsfromdb.h"
#include "idbservice.h"

class DartsUtilityServices
{
public:
    IDbGetIndexesUtility *dbGetIndexesFromjson() const;
    void setDbGetIndexesFromjson(IDbGetIndexesUtility *newDbGetIndexesFromjson);
    IRemoveModelsFromDb<IDbService> *removeModelsFromDb() const;
    void setRemoveModelsFromDb(IRemoveModelsFromDb<IDbService> *newRemoveModelFromDb);

private:
    IDbGetIndexesUtility *_dbGetIndexesFromjson;
    IRemoveModelsFromDb<IDbService> *_removeModelsFromDb;
};

#endif // DARTSUTILITYSERVICES_H

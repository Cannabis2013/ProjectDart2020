#include "dartsutilityservices.h"

IDbGetIndexesUtility *DartsUtilityServices::dbGetIndexesFromjson() const
{
    return _dbGetIndexesFromjson;
}

void DartsUtilityServices::setDbGetIndexesFromjson(IDbGetIndexesUtility *newDbGetIndexesFromjson)
{
    _dbGetIndexesFromjson = newDbGetIndexesFromjson;
}

IRemoveModelsFromDb<IDbService> *DartsUtilityServices::removeModelsFromDb() const
{
    return _removeModelsFromDb;
}

void DartsUtilityServices::setRemoveModelsFromDb(IRemoveModelsFromDb<IDbService> *newRemoveModelFromDb)
{
    _removeModelsFromDb = newRemoveModelFromDb;
}

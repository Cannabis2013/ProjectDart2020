#include "dartsutilityservices.h"

IDbGetIndexesUtility *DartsUtilityServices::dbGetIndexesFromjson() const
{
    return _dbGetIndexesFromjson;
}

void DartsUtilityServices::setDbGetIndexesFromjson(IDbGetIndexesUtility *newDbGetIndexesFromjson)
{
    _dbGetIndexesFromjson = newDbGetIndexesFromjson;
}

IRemoveModelsFromDb<IModelsDbContext> *DartsUtilityServices::removeModelsFromDb() const
{
    return _removeModelsFromDb;
}

void DartsUtilityServices::setRemoveModelsFromDb(IRemoveModelsFromDb<IModelsDbContext> *newRemoveModelFromDb)
{
    _removeModelsFromDb = newRemoveModelFromDb;
}

#include "dartsutilityservices.h"

IDbGetIndexesUtility *DartsUtilityServices::dbGetIndexesFromjson() const
{
    return _dbGetIndexesFromjson;
}

void DartsUtilityServices::setDbGetIndexesFromjson(IDbGetIndexesUtility *newDbGetIndexesFromjson)
{
    _dbGetIndexesFromjson = newDbGetIndexesFromjson;
}

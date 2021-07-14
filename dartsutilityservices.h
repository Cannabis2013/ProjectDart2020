#ifndef DARTSUTILITYSERVICES_H
#define DARTSUTILITYSERVICES_H

#include "idbgetindexesutility.h"

class DartsUtilityServices
{
public:
    IDbGetIndexesUtility *dbGetIndexesFromjson() const;
    void setDbGetIndexesFromjson(IDbGetIndexesUtility *newDbGetIndexesFromjson);
private:
    IDbGetIndexesUtility *_dbGetIndexesFromjson;
};

#endif // DARTSUTILITYSERVICES_H

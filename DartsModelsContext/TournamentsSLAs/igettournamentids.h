#ifndef IGETDARTSTOURNAMENTIDS_H
#define IGETDARTSTOURNAMENTIDS_H

#include <quuid.h>
#include <qvector.h>
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"

class IGetDartsTournamentIds
{
public:
    virtual QVector<QUuid> fromIndexes(const QVector<int> &indexes, const IModelsDbContext *dbContext) const = 0;
};
#endif // IGETTOURNAMNETIDS_H

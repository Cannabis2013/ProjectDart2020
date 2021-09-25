#ifndef IGETDARTSTOURNAMENTFROMDB_H
#define IGETDARTSTOURNAMENTFROMDB_H

#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"

class IGetDartsTournamentFromDb
{
public:
    virtual const IModel<QUuid> *tournament(const QUuid &tournamentId, const IModelsDbContext *dbService) const = 0;
};

#endif // IGETDARTSTOURNAMENTDATA_H

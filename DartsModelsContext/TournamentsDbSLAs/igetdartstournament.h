#ifndef IGETDARTSTOURNAMENT_H
#define IGETDARTSTOURNAMENT_H

#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"

class IGetDartsTournament
{
public:
    virtual IModel<QUuid> *tournament(const QUuid &tournamentId, const IModelsDbContext *dbService) const = 0;
};

#endif // IGETDARTSTOURNAMENTDATA_H

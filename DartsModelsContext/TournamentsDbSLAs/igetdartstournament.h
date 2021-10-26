#ifndef IGETDARTSTOURNAMENT_H
#define IGETDARTSTOURNAMENT_H

#include "ModelsContext/DbSLAs/imodelsdbcontext.h"

class IGetDartsTournament
{
public:
    virtual IModel<QUuid> *get(const QUuid &tournamentId, const IModelsDbContext *dbService) const = 0;
};

#endif // IGETDARTSTOURNAMENTDATA_H

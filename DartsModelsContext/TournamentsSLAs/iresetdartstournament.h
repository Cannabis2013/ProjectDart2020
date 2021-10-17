#ifndef IRESETDARTSTOURNAMENT_H
#define IRESETDARTSTOURNAMENT_H

#include "DartsModelsContext/TournamentsDbSLAs/IDartsDbContext.h"

class IResetDartsTournament
{
public:
    virtual IDartsDbContext *reset(const QUuid &tournamentId, IDartsDbContext *dbContext) const = 0;
};
#endif // IRESETDARTSTOURNAMENT_H

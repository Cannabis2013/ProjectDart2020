#ifndef IGETDARTSINPUTFROMDB_H
#define IGETDARTSINPUTFROMDB_H

#include "DartsModelsContext/DMCInputSLAs/iplayerinput.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"

class IGetDartsInputFromDb
{
public:
    virtual const IModel<QUuid> *get(const QUuid &tournamentId,
                                    const QUuid &playerId,
                                    const int &roundIndex,
                                    const int &attemptIndex,
                                    const IModelsDbContext *dbService) const = 0;
};

#endif // IGETDARTSINPUTFROMDB_H

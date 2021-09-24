#ifndef IGETDARTSINPUTFROMDB_H
#define IGETDARTSINPUTFROMDB_H

#include "igetpointinputfromdb.h"
#include "DartsModelsContext/DMCInputSLAs/iplayerinput.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"

class IGetDartsInputFromDb : public IGetPointInputFromDb<IModel<QUuid>,QUuid,IModelsDbContext>
{
public:
    virtual const IModel<QUuid> *get(const QUuid &tournamentId,
                                    const QUuid &playerId,
                                    const int &roundIndex,
                                    const int &attemptIndex,
                                    const IModelsDbContext *dbService) const override = 0;
};

#endif // IGETDARTSINPUTFROMDB_H

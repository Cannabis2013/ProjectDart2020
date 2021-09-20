#ifndef IGETDARTSPOINTFROMDB_H
#define IGETDARTSPOINTFROMDB_H

#include "igetpointinputfromdb.h"
#include "iplayerinput.h"
#include "ModelsContext/imodelsdbcontext.h"

class IGetDartsPointFromDb : public IGetPointInputFromDb<IModel<QUuid>,QUuid,IModelsDbContext>
{
public:
    virtual const IModel<QUuid> *get(const QUuid &tournamentId,
                                    const QUuid &playerId,
                                    const int &roundIndex,
                                    const int &attemptIndex,
                                    const IModelsDbContext *dbService) const override = 0;
};

#endif // IGETDARTSPOINTFROMDB_H

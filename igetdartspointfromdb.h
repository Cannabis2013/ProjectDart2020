#ifndef IGETDARTSPOINTFROMDB_H
#define IGETDARTSPOINTFROMDB_H

#include "igetpointinputfromdb.h"
#include "iplayerinput.h"
#include "idbservice.h"

class IGetDartsPointFromDb : public IGetPointInputFromDb<IModel<QUuid>,QUuid,IDbService>
{
public:
    virtual const IModel<QUuid> *get(const QUuid &tournamentId,
                                    const QUuid &playerId,
                                    const int &roundIndex,
                                    const int &attemptIndex,
                                    const IDbService *dbService) const override = 0;
};

#endif // IGETDARTSPOINTFROMDB_H

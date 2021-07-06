#ifndef IGETDARTSPOINTFROMDB_H
#define IGETDARTSPOINTFROMDB_H

#include "igetpointinputfromdb.h"
#include "iplayerinput.h"
#include "idartsinputdb.h"

class IGetDartsPointFromDb : public IGetPointInputFromDb<IPlayerInput,QUuid,IDartsInputDb>
{
public:
    virtual const IPlayerInput *get(const QUuid &tournamentId,
                                    const QUuid &playerId,
                                    const int &roundIndex,
                                    const int &attemptIndex,
                                    const IDartsInputDb *dbService) const override = 0;
};

#endif // IGETDARTSPOINTFROMDB_H

#ifndef IGETDARTSSCOREFROMDB_H
#define IGETDARTSSCOREFROMDB_H

#include "igetscoreinputfromdb.h"
#include "iplayerinput.h"
#include "idartsinputdb.h"

class IGetDartsScoreFromDb : public IGetScoreInputFromDb<IPlayerInput,QUuid,IDartsInputDb>
{
public:
    virtual const IPlayerInput *get(const QUuid &tournamentId,
                                    const QUuid &playerId,const int &roundIndex,
                                    const IDartsInputDb *dbService) const override = 0;
};

#endif // IGETDARTSSCOREFROMDB_H

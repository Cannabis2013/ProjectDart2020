#ifndef IGETDARTSSCOREFROMDB_H
#define IGETDARTSSCOREFROMDB_H

#include "igetscoreinputfromdb.h"
#include "iplayerinput.h"
#include "idbservice.h"

class IGetDartsScoreFromDb : public IGetScoreInputFromDb<IModel<QUuid>,QUuid,IDbService>
{
public:
    virtual const IModel<QUuid> *get(const QUuid &tournamentId,
                                     const QUuid &playerId,const int &roundIndex,
                                     const IDbService *dbService) const override = 0;
};

#endif // IGETDARTSSCOREFROMDB_H

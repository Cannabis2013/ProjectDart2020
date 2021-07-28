#ifndef IGETDARTSSCOREFROMDB_H
#define IGETDARTSSCOREFROMDB_H

#include "igetscoreinputfromdb.h"
#include "iplayerinput.h"
#include "imodelsdbcontext.h"

class IGetDartsScoreFromDb : public IGetScoreInputFromDb<IModel<QUuid>,QUuid,IModelsDbContext>
{
public:
    virtual const IModel<QUuid> *get(const QUuid &tournamentId,
                                     const QUuid &playerId,const int &roundIndex,
                                     const IModelsDbContext *dbService) const override = 0;
};

#endif // IGETDARTSSCOREFROMDB_H

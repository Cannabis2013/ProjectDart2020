#ifndef ICREATETOURNAMENTWINNERJSON_H
#define ICREATETOURNAMENTWINNERJSON_H

#include <icreatejsonfromplayers.h>
#include <igetplayerfromdb.h>
#include "ModelsContext/imodelsdbcontext.h"

class ICreateTournamentWinnerJson
{
public:
    virtual QByteArray createJson(const QUuid &winnerId,
                                  const IGetPlayersFromDb *getPlayerModels,
                                  const ICreateJsonFromPlayers *jsonBuilder,
                                  const IModelsDbContext *dbService) const = 0;
};

#endif // ICREATETOURNAMENTWINNERJSON_H

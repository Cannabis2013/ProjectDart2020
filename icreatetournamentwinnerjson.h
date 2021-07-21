#ifndef ICREATETOURNAMENTWINNERJSON_H
#define ICREATETOURNAMENTWINNERJSON_H

#include <idartsplayerjsonbuilder.h>
#include <igetdartsplayermodelsfromdb.h>
#include "idbservice.h"

class ICreateTournamentWinnerJson
{
public:
    virtual QByteArray createJson(const QUuid &winnerId,
                                  const IGetDartsPlayerModelsFromDb *getPlayerModels,
                                  const IDartsPlayerJsonBuilder *jsonBuilder,
                                  const IDbService *dbService) const = 0;
};

#endif // ICREATETOURNAMENTWINNERJSON_H

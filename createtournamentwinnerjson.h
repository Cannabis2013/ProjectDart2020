#ifndef CREATETOURNAMENTWINNERJSON_H
#define CREATETOURNAMENTWINNERJSON_H

#include "icreatetournamentwinnerjson.h"
class CreateTournamentWinnerJson : public ICreateTournamentWinnerJson
{
public:
    virtual QByteArray createJson(const QUuid &winnerId,
                                  const IGetDartsPlayerModelsFromDb *getPlayerModels,
                                  const IDartsPlayerJsonBuilder *jsonBuilder,
                                  const IPlayerModelsDb *dbService) const override
    {
        auto playerModel = getPlayerModels->playerModel(winnerId,dbService);
        auto responseJson = jsonBuilder->createJson(playerModel);
        return responseJson;
    }
};

#endif // CREATETOURNAMENTWINNERJSON_H

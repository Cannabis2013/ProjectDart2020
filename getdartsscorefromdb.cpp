#include "getdartsscorefromdb.h"

using namespace DartsModelsContext;

const IPlayerInput *GetDartsScoreFromDb::get(const QUuid &tournamentId,
                                             const QUuid &playerId,
                                             const int &roundIndex,
                                             const IDartsInputDb *dbService) const
{
    auto models = dbService->models();
    auto model = getModelThatMatchesParameters(models,tournamentId,playerId,roundIndex);
    return model;
}

const IPlayerInput *GetDartsScoreFromDb::getModelThatMatchesParameters(const QVector<const IPlayerInput *> &models,
                                                                 const QUuid &tournamentId, const QUuid &playerId,
                                                                 const int &roundIndex) const
{
    for (const auto &model : models) {
        if(matchParameters(model,tournamentId,playerId,roundIndex))
            return model;
    }
    throw "Model not found";
}

bool GetDartsScoreFromDb::matchParameters(const IPlayerInput *input, const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex) const
{
    auto model = dynamic_cast<const IDartsInput*>(input);
    if(model->tournamentId() != tournamentId)
        return false;
    else if(model->playerId() != playerId)
        return false;
    else if(model->roundIndex() != roundIndex)
        return false;
    else
        return true;
}

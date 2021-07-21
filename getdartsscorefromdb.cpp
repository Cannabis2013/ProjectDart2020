#include "getdartsscorefromdb.h"

using namespace ModelsContext;

const IModel<QUuid> *GetDartsScoreFromDb::get(const QUuid &tournamentId,
                                             const QUuid &playerId,
                                             const int &roundIndex,
                                             const IDbService *dbService) const
{
    auto models = dbService->models();
    auto model = getModelThatMatchesParameters(models,tournamentId,playerId,roundIndex);
    return model;
}

const IModel<QUuid> *GetDartsScoreFromDb::getModelThatMatchesParameters(const QVector<const IModel<QUuid>*> &models,
                                                                 const QUuid &tournamentId, const QUuid &playerId,
                                                                 const int &roundIndex) const
{
    for (const auto &model : models) {
        if(matchParameters(model,tournamentId,playerId,roundIndex))
            return model;
    }
    throw "Model not found";
}

bool GetDartsScoreFromDb::matchParameters(const IModel<QUuid> *input, const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex) const
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

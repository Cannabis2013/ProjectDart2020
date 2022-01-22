#include "dartssetwinner.h"
#include <quuid.h>
#include <qvector.h>
#include "ModelSLAs/imodel.h"
#include "TournamentModelsSLAs/idartstournament.h"

void DartsSetWinner::setWinner(const QUuid &tournamentId, const Models &models, const QString &playerName, const QUuid &playerId) const
{
    auto model = findModel(tournamentId,models);
    auto tournament = dynamic_cast<IDartsTournament*>(model);
    tournament->setWinnerId(playerId);
    tournament->setWinnerName(playerName);
}

DartsSetWinner::Model *DartsSetWinner::findModel(const QUuid &tournamentId, const Models &models) const
{
    for (const auto &model : models) {
        if(model->id() == tournamentId)
            return model;
    }
    return nullptr;
}

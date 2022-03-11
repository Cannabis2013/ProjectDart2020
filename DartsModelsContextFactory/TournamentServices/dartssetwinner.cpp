#include "dartssetwinner.h"
#include <quuid.h>
#include <qvector.h>
#include "ModelSLAs/imodel.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include "Models/DartsPlayer.h"
#include "SLAs/dartsmodelsservices.h"
#include "ForeignContextSLAs/DartsPlayerServices.h"
#include "TournamentsSLAs/tournamentservices.h"

bool DartsSetWinner::setWinner(const QUuid &tournamentId, const QString &playerName, DartsModelsServices *services)
{
    auto tournament = getTournament(tournamentId,services);
    auto player = getPlayer(playerName,services);
    updateTournament(tournament,player);
    return persistChanges(services);
}

IDartsTournament *DartsSetWinner::getTournament(const QUuid &tournamentId, DartsModelsServices *services) const
{
    auto dbContext = services->tournamentServices()->dbContext();
    auto models = dbContext->models();
    for (const auto &model : qAsConst(models)) {
        if(model->id() == tournamentId)
            return dynamic_cast<IDartsTournament*>(model);
    }
    return nullptr;
}

DartsPlayer DartsSetWinner::getPlayer(const QString &name, DartsModelsServices *services) const
{
    auto playersContext = services->playersContext();
    auto playerServices = services->playerServices();
    auto plaBa = playersContext->player(name);
    if(plaBa == QByteArray()) return DartsPlayer();
    return playerServices->playerConverter()->player(plaBa);
}

void DartsSetWinner::updateTournament(IDartsTournament *tournament ,const DartsPlayer &player)
{
    tournament->setWinnerId(player.id);
    tournament->setWinnerName(player.name);
}

bool DartsSetWinner::persistChanges(DartsModelsServices *services)
{
    auto dbContext = services->tournamentServices()->dbContext();
    return dbContext->saveChanges();
}

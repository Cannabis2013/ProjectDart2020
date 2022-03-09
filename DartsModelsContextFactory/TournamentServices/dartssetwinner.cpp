#include "dartssetwinner.h"
#include <quuid.h>
#include <qvector.h>
#include "ModelSLAs/imodel.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include "Models/DartsPlayer.h"
#include "SLAs/dartsmodelsservices.h"
#include "ForeignContextSLAs/DartsPlayerServices.h"
#include "TournamentsSLAs/tournamentservices.h"

void DartsSetWinner::setWinner(const QUuid &tournamentId, const QString &playerName, DartsModelsServices *services) const
{
    auto tournament = getTournament(tournamentId,services);
    auto player = getPlayer(playerName,services);
    tournament->setWinnerId(player.id);
    tournament->setWinnerName(player.name);
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

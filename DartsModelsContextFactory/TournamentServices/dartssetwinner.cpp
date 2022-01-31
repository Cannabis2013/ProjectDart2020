#include "dartssetwinner.h"
#include <quuid.h>
#include <qvector.h>
#include "ModelSLAs/imodel.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include "Models/DartsPlayer.h"
#include "SLAs/dmcservices.h"
#include "ForeignContextSLAs/DartsPlayerServices.h"
#include "TournamentsSLAs/dartsservices.h"

DartsSetWinner::DartsSetWinner(DMCServices *services):_services(services)
{
    _tnmServices = _services->tournamentServices();
    _plaServices = _services->playerServices();
}

void DartsSetWinner::setWinner(const QUuid &tournamentId, const QString &playerName) const
{
    auto tournament = getTournament(tournamentId);
    auto player = getPlayer(playerName);
    tournament->setWinnerId(player.id);
    tournament->setWinnerName(player.name);
}

IDartsTournament *DartsSetWinner::getTournament(const QUuid &tournamentId) const
{
    auto models = _tnmServices->dartsDbCtx()->models();
    for (const auto &model : models) {
        if(model->id() == tournamentId)
            return dynamic_cast<IDartsTournament*>(model);
    }
    return nullptr;
}

DartsPlayer DartsSetWinner::getPlayer(const QString &name) const
{
    auto plaBa = _services->playersContext()->player(name);
    if(plaBa == QByteArray()) return DartsPlayer();
    return _plaServices->playerConverter()->player(plaBa);
}

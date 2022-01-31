#include "dartstournamentrepair.h"
#include "SLAs/dmcservices.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include "ContextSLA/absplactx.h"
#include "Models/DartsPlayer.h"
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

DartsTournamentRepair::DartsTournamentRepair(DMCServices *services):_services(services)
{
    _plaCtx = services->playersContext();
    _tnmServices = services->tournamentServices();
    _iptServices = services->inputServices();
    _plaServices = services->playerServices();
}

bool DartsTournamentRepair::repair(const QUuid &tournamentID) const
{
    auto tournament = getTournament(tournamentID);
    auto inputs = getInputs(tournamentID);
    auto r = repairTournamentPlayers(dynamic_cast<IDartsTournament*>(tournament));
    r = repairInputs(inputs)? true : r;
    return r;
}

DartsTournamentRepair::Model *DartsTournamentRepair::getTournament(const QUuid &tournamentID) const
{
    auto dartsDb = _tnmServices->dartsDbCtx();
    auto models = dartsDb->models();
    return _tnmServices->getTournament()->get(tournamentID,models);
}

DartsTournamentRepair::Models DartsTournamentRepair::getInputs(const QUuid &tournamentID) const
{
    auto inputsDb = _iptServices->inputsDb();
    auto getInputs = _iptServices->getInputsFromDb();
    return getInputs->get(tournamentID,inputsDb->models());
}

bool DartsTournamentRepair::repairTournamentPlayers(IDartsTournament *tournament) const
{
    auto names = tournament->playerNames();
    auto plaBa = _plaCtx->players(names);
    auto players = toPlayers(plaBa);
    if(names.count() > players.count())
        return false;
    QVector<QUuid> pIds;
    QVector<QString> pNames;
    for (const auto &player : players) {
        pIds << player.id;
        pNames << player.name;
    }
    tournament->setPlayerIds(pIds);
    tournament->setPlayerNames(pNames);
    return true;
}

bool DartsTournamentRepair::repairInputs(const Models &models) const
{
    for (auto &model : models) {
        auto input = dynamic_cast<IDartsInput*>(model);
        auto playerId = input->playerId();
        auto playerName = input->playerName();
        auto plaBa = _plaCtx->player(playerId);
        if(plaBa != QByteArray()) continue;
        plaBa = _plaCtx->player(playerName);
        if(plaBa == QByteArray()) return false;
        auto player = _plaServices->playerConverter()->player(plaBa);
        input->setPlayerId(player.id);
        input->setPlayerName(player.name);
    }
    return true;
}

DartsTournamentRepair::Players DartsTournamentRepair::toPlayers(const QByteArray &byteArray) const
{
    Players players;
    auto arr = QJsonDocument::fromJson(byteArray).array();
    for (const auto &jsonValue : qAsConst(arr))
        players << _plaServices->playerConverter()->player(jsonValue.toObject());
    return players;
}

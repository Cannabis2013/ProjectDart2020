#include "dartstournamentrepair.h"
#include "SLAs/dartsmodelsservices.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include "ContextSLA/absplactx.h"
#include "Models/DartsPlayer.h"
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

bool DartsTournamentRepair::repair(const QUuid &tournamentID, DartsModelsServices *services)
{
    auto tournament = getTournament(tournamentID,services);
    auto inputs = getInputs(tournamentID,services);
    auto result = repairTournamentPlayers(tournament,services);
    result = repairInputs(inputs, services)? true : result;
    if(!result)
        return false;
    return persistChanges(services);
}

DartsTournamentRepair::PlayerDetails DartsTournamentRepair::getPlayerDetails(const Players &players)
{
    QVector<QUuid> IDs;
    QVector<QString> names;
    for (const auto &player : qAsConst(players)) {
        IDs << player.id;
        names << player.name;
    }
    return {.IDs = IDs,.names = names};
}

IDartsTournament *DartsTournamentRepair::getTournament(const QUuid &tournamentID, DartsModelsServices *services)
{
    auto dartsDb = services->tournamentServices()->dbContext();
    auto models = dartsDb->models();
    auto model = services->tournamentServices()->getTournament()->get(tournamentID,models);
    return dynamic_cast<IDartsTournament*>(model);
}

DartsTournamentRepair::Models DartsTournamentRepair::getInputs(const QUuid &tournamentID, DartsModelsServices *services)
{
    auto models = services->inputServices()->dbContext()->models();
    return services->inputServices()->getInputsFromDb()->get(tournamentID,models);
}

bool DartsTournamentRepair::repairTournamentPlayers(IDartsTournament *tournament, DartsModelsServices *services)
{
    auto names = tournament->playerNames();
    auto plaBa = services->playersContext()->players(names);
    auto players = toPlayers(plaBa,services);
    if(names.count() > players.count())
        return false;
    auto details = getPlayerDetails(players);
    tournament->setPlayerIds(details.IDs);
    tournament->setPlayerNames(details.names);
    return true;
}

bool DartsTournamentRepair::repairInputs(const Models &models, DartsModelsServices *services)
{
    for (auto &model : models) {
        auto input = dynamic_cast<IDartsInput*>(model);
        auto playerId = input->playerId();
        auto playerName = input->playerName();
        auto plaBa = services->playersContext()->player(playerId);
        if(plaBa != QByteArray()) continue;
        plaBa = services->playersContext()->player(playerName);
        if(plaBa == QByteArray()) return false;
        auto player = services->playerServices()->playerConverter()->player(plaBa);
        input->setPlayerId(player.id);
        input->setPlayerName(player.name);
    }
    return true;
}

DartsTournamentRepair::Players DartsTournamentRepair::toPlayers(const QByteArray &byteArray, DartsModelsServices *services)
{
    Players players;
    auto converter = services->playerServices()->playerConverter();
    auto arr = QJsonDocument::fromJson(byteArray).array();
    for (const auto &jsonValue : qAsConst(arr))
        players << converter->player(jsonValue.toObject());
    return players;
}

bool DartsTournamentRepair::persistChanges(DartsModelsServices *services)
{
    auto tournamentDb = services->tournamentServices()->dbContext();
    auto inputDb = services->inputServices()->dbContext();
    auto tournamentSaved = tournamentDb->saveChanges();
    auto inputsSaved = inputDb->saveChanges();
    return tournamentSaved && inputsSaved;
}

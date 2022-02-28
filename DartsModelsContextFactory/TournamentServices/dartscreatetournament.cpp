#include "dartscreatetournament.h"
#include "SLAs/dartsmodelsservices.h"
#include "Models/DartsPlayer.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include <qjsonarray.h>
#include <qjsondocument.h>

DartsCreateTournament::DartsCreateTournament(DartsModelsServices *services){
    _dartsBuilder = services->tournamentServices()->tournamentBuilder();
    _playersContext = services->playersContext();
    _playerConverter = services->playerServices()->playerConverter();
}

DartsCreateTournament::Model *DartsCreateTournament::create(const ByteArray &byteArray, const Indexes &playerIndexes) const
{
    auto tournament = _dartsBuilder->createModel(byteArray);
    auto playersByteArray = _playersContext->players(playerIndexes);
    auto players = convertPlayers(playersByteArray);
    addTournamentDetails(tournament,players);
    return tournament;
}

DartsCreateTournament::Players DartsCreateTournament::convertPlayers(const ByteArray &playersBa) const
{
    Players players;
    QJsonArray arr = QJsonDocument::fromJson(playersBa).array();
    for (const auto &jsonValue : qAsConst(arr)) {
        auto player = _playerConverter->player(jsonValue.toObject());
        players << player;
    }
    return players;
}

void DartsCreateTournament::addTournamentDetails(Model *model, const Players &players) const
{
    auto tournament = dynamic_cast<IDartsTournament*>(model);
    auto playerIDs = createPlayerIds(players);
    auto playerNames = createPlayerNames(players);
    tournament->setPlayerIds(playerIDs);
    tournament->setPlayerNames(playerNames);
}

QVector<QUuid> DartsCreateTournament::createPlayerIds(const Players &players) const
{
    QVector<QUuid> playerIds;
    for (const auto &player : players)
        playerIds << player.id;
    return playerIds;
}

QVector<QString> DartsCreateTournament::createPlayerNames(const Players &players) const
{
    QVector<QString> playerNames;
    for (const auto &player : players)
        playerNames << player.name;
    return playerNames;
}

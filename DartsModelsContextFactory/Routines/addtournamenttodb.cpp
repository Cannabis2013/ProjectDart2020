#include "addtournamenttodb.h"
#include "SLAs/dartsmodelsservices.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include "TournamentModelsSLAs/idartstournament.h"
#include <Models/DartsPlayer.h>

bool AddTournamentToDb::add(const QByteArray &byteArray, const Indexes &indexes, Services *services)
{
    auto tournament = createTournamentModel(byteArray,services);
    addPlayerDetails(tournament,indexes,services);
    addModelToMemory(tournament,services);
    return persistModel(services);
}

IDartsTournament *AddTournamentToDb::createTournamentModel(const QByteArray &byteArray, Services *services)
{
    auto json = QJsonDocument::fromJson(byteArray).object();
    auto cvtr = services->tournamentServices()->dartsConverter();
    auto model = cvtr->create(json);
    auto tournament = dynamic_cast<IDartsTournament*>(model);
    return tournament;
}

void AddTournamentToDb::addPlayerDetails(IDartsTournament *tournament, const Indexes &indexes, Services *services)
{
    auto playersContext = services->playersContext();
    auto byteArray = playersContext->players(indexes);
    auto players = toPlayerModels(byteArray,services);
    for (const auto &player : qAsConst(players)) {
        tournament->playerIds().append(player.id);
        tournament->playerNames().append(player.name);
    }
}

AddTournamentToDb::Players AddTournamentToDb::toPlayerModels(const QByteArray &byteArray, Services *services)
{
    auto cvtr = services->playerServices()->playerConverter();
    Players playerModels;
    auto arr = QJsonDocument::fromJson(byteArray).array();
    for (const auto &jVal : qAsConst(arr)) {
        auto player = cvtr->player(jVal.toObject());
        playerModels << player;
    }
    return playerModels;
}

void AddTournamentToDb::addModelToMemory(IDartsTournament *tournament, Services *services)
{
    auto tournamentServices= services->tournamentServices();
    auto dbContext = tournamentServices->dbContext();
    dbContext->add(tournament);
}

bool AddTournamentToDb::persistModel(Services *services)
{
    auto tournamentDb = services->tournamentServices()->dbContext();
    return tournamentDb->saveChanges();
}


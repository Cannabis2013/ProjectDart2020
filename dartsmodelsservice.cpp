#include "dartsmodelsservice.h"

using namespace DartsModelsContext;

DartsModelsService *DartsModelsService::createInstance()
{
    return new DartsModelsService();
}

const IDartsTournament *DartsModelsService::dartsTournamentModelById(const QUuid &tournamentId) const
{
    auto model = _getDartsTournamentByIdService->service(tournamentId,_tournamentsDbContext);
    return model;
}

const IDartsTournament *DartsModelsService::dartsTournamentByIndex(const int& index) const
{
    auto model = _getDartsTournamentByIndexService->service(index,_tournamentsDbContext);
    return model;
}

QUuid DartsModelsService::addDartsTournamentToDb(const IDartsTournament* tournament)
{
    _tournamentsDbContext->addTournament(tournament);
    return tournament->id();
}

bool DartsModelsService::removeTournamentsByIndexes(const QVector<int> &indexes) const
{
    return _deleteTournamentsByIndexes->service(indexes,_tournamentsDbContext);
}

void DartsModelsService::tournamentSetWinnerId(const QUuid &tournamentId,
                                               const QUuid &winnerId)
{
    auto oldModel = _getDartsTournamentByIdService->service(tournamentId,_tournamentsDbContext);
    auto newModel = const_cast<IDartsTournament*>(oldModel);
    newModel->setWinnerId(winnerId);
    auto index = _tournamentsDbContext->indexOfTournament(oldModel);
    _tournamentsDbContext->replaceTournament(index,newModel);
}

DartsModelsService *DartsModelsService::setGetDartsTournamentByIdService(GetDartsTournamentByIdService *service)
{
    _getDartsTournamentByIdService = service;
    return this;
}

DartsModelsService *DartsModelsService::setGetTournamentByIndexService(GetTournamentByIndexService *service)
{
    _getDartsTournamentByIndexService = service;
    return this;
}

DartsModelsService *DartsModelsService::setDartsScoresDb(IDartsScoreDb *dartsScoresDb)
{
    _dartsScoresDb = dartsScoresDb;
    return this;
}

DartsModelsService *DartsModelsService::setAssignPlayerIdsToDartsTournament(AssignPlayerIdsToTournament *newAssignPlayerIdsToDartsTournament)
{
    _assignPlayerIdsToDartsTournament = newAssignPlayerIdsToDartsTournament;
    return this;
}

DartsModelsService *DartsModelsService::setDeleteTournamentsByIndexes(DeleteTournamentByIndexes *service)
{
    _deleteTournamentsByIndexes = service;
    return this;
}

DartsModelsService *DartsModelsService::setDartsScoreDb(IDartsScoreDb *dartsScoreDb)
{
    _dartsScoresDb = dartsScoreDb;
    return this;
}

DartsModelsService* DartsModelsService::setTournamentsDbContext(IDartsTournamentDb *tournamentsDbContext)
{
    _tournamentsDbContext = tournamentsDbContext;
    return this;
}


DartsModelsService* DartsModelsService::setDartsPointsDb(IDartsPointDb *dartsPointsDb)
{
    _dartsPointsDb = dartsPointsDb;
    return this;
}

QVector<const IDartsTournament *> DartsModelsService::dartsTournamentModels() const
{
    auto models = _tournamentsDbContext->dartsTournaments();
    return models;
}

const IDartsTournament *DartsModelsContext::DartsModelsService::assignPlayerIdsToDartsTournament(const IDartsTournament *tournament, const QVector<QUuid> &playerIds) const
{
    auto model = _assignPlayerIdsToDartsTournament->service(tournament,playerIds);
    return model;
}

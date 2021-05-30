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

void DartsModelsService::setDartsPointHint(const PlayerInput* inputModel,
                                                                             const int &hint)
{
    _setInputHintService->service(inputModel,hint);
    _dartsPointsDb->saveState();
}

void DartsModelsService::removePointsByTournamentId(const QUuid &tournamentId)
{
    auto models = _dartsPointsDb->models();
    auto playerInputs = _dartsInputsFilterService->filterByTournamentId(models,tournamentId);
    _removeModelsService->service(playerInputs,_dartsPointsDb);
}

void DartsModelsService::removePointById(const QUuid &pointId)
{
    try {
        auto scoreModel = _getInputModelByIdService->service(pointId,_dartsPointsDb);
        auto index = _dartsPointsDb->indexOfModel(scoreModel);
        _dartsPointsDb->removeModelByIndex(index);
    } catch (const char *msg) {
        return;
    }
}

DartsModelsService *DartsModelsService::setGetScoreIndexesByTournamentId(GetScoreIndexesByDartsTournamentService *service)
{
    _getDartsScoreIndexesByModels = service;
    return this;
}

DartsModelsService *DartsModelsService::setGetDartsInputModelByIdService(GetDartsInputModelByIdService *service)
{
    _getInputModelByIdService = service;
    return this;
}

DartsModelsService *DartsModelsService::setDartsPointModelHintService(setInputHintService *service)
{
    _setInputHintService = service;
    return this;
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

DartsModelsService *DartsModelsService::setRemoveModelsService(RemoveModelsService* newRemoveModelsService)
{
    _removeModelsService = newRemoveModelsService;
    return this;
}

DartsModelsService* DartsModelsService::setDartsPointLessThanPredicate(IPredicate* predicate)
{
    _dartsPointLessThanPredicate = predicate;
    return this;
}


DartsModelsService *DartsModelsService::setDartsScoreLessThanPredicate(IPredicate *predicate)
{
    _dartsScoreLessThanPredicate = predicate;
    return this;
}

DartsModelsService *DartsModelsService::setDartsInputsFilterService(FilterDartsInputsService *newFilterDartsInputsService)
{
    _dartsInputsFilterService = newFilterDartsInputsService;
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

DartsModelsService *DartsModelsService::setGetOrderedDartsScoreModels(SortDartsInputsByPredicateService *service)
{
    _sortDartsInputModelsByPredicate = service;
    return this;
}

const IDartsPointIndexes* DartsModelsService::dartsPointIndexes(const QUuid &tournamentId) const
{
    auto dartsInputs = _dartsPointsDb->models();
    auto tournamentInputs = _dartsInputsFilterService->filterByTournamentId(dartsInputs,tournamentId);
    auto orderedModels = _sortDartsInputModelsByPredicate->service(tournamentInputs,_dartsPointLessThanPredicate);
    auto model = _getDartsTournamentByIdService->service(tournamentId,_tournamentsDbContext);
    auto count = dartsPointsCount(tournamentId,ModelDisplayHint::DisplayHint);
    auto indexes = _assembleDartsPointIndexes->service(orderedModels,model,count);
    return indexes;
}

QVector<const DartsModelsService::PlayerInput*> DartsModelsService::dartsPointModelsByTournamentId(const QUuid &tournamentId) const
{
    auto dartsInputs = _dartsPointsDb->models();
    auto tournamentInputs = _dartsInputsFilterService->filterByTournamentId(dartsInputs,tournamentId);
    return tournamentInputs;
}

const DartsModelsService::PlayerInput *DartsModelsService::getDartsPointModelById(const QUuid &pointId) const
{
    auto pointModel = _getInputModelByIdService->service(pointId,_dartsPointsDb);
    return pointModel;
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

DartsModelsService *DartsModelsService::setAssembleDartsPointIndexes(GetPointIndexesFromDartsTournamentService *service)
{
    _assembleDartsPointIndexes = service;
    return this;
}

int DartsModelsService::dartsPointsCount(const QUuid &tournamentId, const int &hint) const
{
    auto pointInputs = _dartsInputsFilterService->filterByHint(_dartsPointsDb->models(),tournamentId,hint);
    return pointInputs.count();
}

void DartsModelsService::addDartsPoint(const DartsModelsService::PlayerInput *model)
{
    _dartsPointsDb->addModel(model);
}

QVector<const DartsModelsService::PlayerInput *> DartsModelsService::getDartsPointModelsOrdedByIndexes(const QUuid &tournamentId) const
{
    auto dartsInputs = _dartsPointsDb->models();
    auto tournamentInputs = _dartsInputsFilterService->filterByTournamentId(dartsInputs,tournamentId);
    auto orderedPlayerInputs = _sortDartsInputModelsByPredicate->service(tournamentInputs,_dartsPointLessThanPredicate);
    return orderedPlayerInputs;
}

void DartsModelsService::removeHiddenPoints(const QUuid &tournamentId)
{
    auto dartsPointInputs = _dartsInputsFilterService->filterByHint(_dartsPointsDb->models(),tournamentId,HiddenHint);
    _removeModelsService->service(dartsPointInputs,_dartsPointsDb);
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


const DartsModelsService::PlayerInput *DartsModelsContext::DartsModelsService::dartsPointModel(const QUuid &tournamentId,
                                                                                               const QUuid &playerId,
                                                                                               const int &roundIndex,
                                                                                               const int &attemptIndex) const
{
    auto models = _dartsPointsDb->models();
    auto pointModelsByAttemptIndex = _dartsInputsFilterService->filterByAttemptIndex(models,tournamentId,playerId,roundIndex,AllHints,attemptIndex);
    auto firstModel = pointModelsByAttemptIndex.first();
    return firstModel;
}

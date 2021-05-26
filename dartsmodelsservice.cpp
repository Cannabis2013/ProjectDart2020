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

const DartsModelsService::PlayerInput *DartsModelsService::setDartsPointHint(const QUuid &tournamentId,
                                                                             const QUuid &playerId,
                                                                             const int &roundIndex,
                                                                             const int &attempt,
                                                                             const int &hint)
{
    auto pointInputs = _dartsPointsDb->models();
    auto models = _dartsInputsFilterService->filterByAttemptIndex(pointInputs,tournamentId,playerId,roundIndex,DisplayHint,attempt);
    auto model = models.first();
    auto alteredModel = _setInputHintService->service(model,hint);
    return alteredModel;
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

DartsModelsService *DartsModelsService::setGetScoreIndexesByTournamentId(GetScoreIndexesByDartsTournamentService *getScoreIndexesByTournamentId)
{
    _getDartsScoreIndexesByModels = getScoreIndexesByTournamentId;
    return this;
}

DartsModelsService *DartsModelsService::setGetDartsInputModelByIdService(GetDartsInputModelByIdService *getDartsPointByIdService)
{
    _getInputModelByIdService = getDartsPointByIdService;
    return this;
}

DartsModelsService *DartsModelsService::setDartsPointModelHintService(setInputHintService *dartsPointModelHintService)
{
    _setInputHintService = dartsPointModelHintService;
    return this;
}

DartsModelsService *DartsModelsService::setGetDartsTournamentByIdService(GetDartsTournamentByIdService *getDartsTournamentByIdService)
{
    _getDartsTournamentByIdService = getDartsTournamentByIdService;
    return this;
}

DartsModelsService *DartsModelsService::setGetTournamentByIndexService(GetTournamentByIndexService *newGetTournamentByIndexService)
{
    _getDartsTournamentByIndexService = newGetTournamentByIndexService;
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

DartsModelsService* DartsModelsService::setDartsPointLessThanPredicate(Predicate* predicate)
{
    _dartsPointLessThanPredicate = predicate;
    return this;
}


DartsModelsService *DartsModelsService::setDartsScoreLessThanPredicate(Predicate *predicate)
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

DartsModelsService *DartsModelsService::setDeleteTournamentsByIndexes(DeleteTournamentByIndexes *deleteTournamentsByIndexes)
{
    _deleteTournamentsByIndexes = deleteTournamentsByIndexes;
    return this;
}

DartsModelsService *DartsModelsService::setDartsScoreDb(IDartsScoreDb *dartsScoreDb)
{
    _dartsScoresDb = dartsScoreDb;
    return this;
}

DartsModelsService *DartsModelsService::setGetOrderedDartsScoreModels(SortDartsInputsByPredicateService *getOrderedDartsScoreModels)
{
    _sortDartsInputModelsByPredicate = getOrderedDartsScoreModels;
    return this;
}

const DartsModelsService::PlayerInput *DartsModelsService::dartsScoreModel(const QUuid& tournamentId,
                                                                           const QUuid& playerId,
                                                                           const int& roundIndex) const
{
    auto scoreInputs = _dartsScoresDb->models();
    auto scoreModelsByRoundIndex = _dartsInputsFilterService->filterByRoundIndex(scoreInputs,tournamentId,playerId,roundIndex);
    auto model = scoreModelsByRoundIndex.first();
    return model;
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

DartsModelsService *DartsModelsService::setAssembleDartsPointIndexes(GetPointIndexesFromDartsTournamentService *getDartsPointIndexes)
{
    _assembleDartsPointIndexes = getDartsPointIndexes;
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

void DartsModelsService::addDartsScore(const IDartsScoreInput* pointModel)
{
    _dartsScoresDb->addModel(pointModel);
}

int DartsModelsService::dartsScoresCount(const int &hint) const
{
    auto count = 0;
    auto models = _dartsScoresDb->models();
    for (const auto& model : models) {
        if(model->hint() == hint)
            count++;
    }
    return count;
}

const DartsModelsService::PlayerInput *DartsModelsService::setDartsScoreHint(const DartsModelsService::PlayerInput *model,
                                                              const int &hint)
{
    auto indexOfModel = _dartsScoresDb->indexOfModel(model);
    auto alteredModel = _setInputHintService->service(model,hint);
    _dartsScoresDb->replaceModel(indexOfModel,alteredModel);
    return alteredModel;
}

void DartsModelsService::removeScoreById(const QUuid &scoreId)
{
    auto model = _getInputModelByIdService->service(scoreId,_dartsScoresDb);
    auto indexOfModel = _dartsScoresDb->indexOfModel(model);
    _dartsScoresDb->removeModelByIndex(indexOfModel);
}

void DartsModelsService::removeHiddenScores(const QUuid &tournamentId)
{
    auto dartsScoreInputs = _dartsInputsFilterService->filterByHint(_dartsPointsDb->models(),tournamentId,HiddenHint);
    _removeModelsService->service(dartsScoreInputs,_dartsScoresDb);
}

void DartsModelsService::removeScoresByTournamentId(const QUuid &tournamentId)
{
    auto dartsScoreInputs = _dartsScoresDb->models();
    auto tournamentScoreInputs = _dartsInputsFilterService->filterByTournamentId(dartsScoreInputs,tournamentId);
    _removeModelsService->service(tournamentScoreInputs,_dartsScoresDb);
}

void DartsModelsService::removeScoreModel(const QUuid &scoreId)
{
    auto model = _getInputModelByIdService->service(scoreId,_dartsScoresDb);
    auto indexOfModel = _dartsScoresDb->indexOfModel(model);
    _dartsScoresDb->removeModelByIndex(indexOfModel);
}


QVector<const IDartsTournament *> DartsModelsService::dartsTournamentModels() const
{
    auto models = _tournamentsDbContext->dartsTournaments();
    return models;
}

const IDartsScoreIndexes *DartsModelsService::dartsScoreIndexes(const QUuid&tournamentId) const
{
    auto dartsScoreInputs = _dartsInputsFilterService->filterByHint(_dartsScoresDb->models(),tournamentId,DisplayHint);
    auto orderedPlayerInputs = _sortDartsInputModelsByPredicate->service(dartsScoreInputs,_dartsScoreLessThanPredicate);
    auto model = _getDartsTournamentByIdService->service(tournamentId,_tournamentsDbContext);
    auto indexes = _getDartsScoreIndexesByModels->service(orderedPlayerInputs,model,dartsScoreInputs.count());
    return indexes;
}


int DartsModelsService::dartsScoreCount(const QUuid &tournamentId,
                                        const int &hint) const
{
    auto dartsScoreInputs = _dartsInputsFilterService->filterByHint(_dartsScoresDb->models(),tournamentId,hint);
    return dartsScoreInputs.count();
}

QVector<const DartsModelsService::PlayerInput *> DartsModelsService::dartsScoreModelsByTournamentIdAndHint(const QUuid &tournamentId,
                                                                                                           const int& hint) const
{
    auto dartsScoreInputs = _dartsInputsFilterService->filterByHint(_dartsScoresDb->models(),tournamentId,hint);
    return dartsScoreInputs;
}


const IDartsTournament *DartsModelsContext::DartsModelsService::assignPlayerIdsToDartsTournament(const IDartsTournament *tournament, const QVector<QUuid> &playerIds) const
{
    auto model = _assignPlayerIdsToDartsTournament->service(tournament,playerIds);
    return model;
}

#include "dartsmodelsservice.h"

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

void DartsModelsService::tournamentAssignPlayer(const QUuid &tournamentId, const QUuid &player)
{
    auto oldModel = _getDartsTournamentByIdService->service(tournamentId,_tournamentsDbContext);
    auto assignedPlayers = oldModel->assignedPlayerIdentities();
    assignedPlayers.append(player);
    auto newModel = const_cast<IDartsTournament*>(oldModel);
    newModel->setAssignedPlayerIdentities(assignedPlayers);
    auto index = _tournamentsDbContext->indexOfTournament(oldModel);
    _tournamentsDbContext->replaceTournament(index,newModel);
}

void DartsModelsService::tournamentAssignPlayers(const QUuid &tournamentId,
                                                 const QVector<QUuid> &playersIds)
{
    auto oldModel = _getDartsTournamentByIdService->service(tournamentId,_tournamentsDbContext);;
    auto newModel = const_cast<IDartsTournament*>(oldModel);
    auto assignedPlayers = newModel->assignedPlayerIdentities();
    assignedPlayers.append(playersIds);
    newModel->setAssignedPlayerIdentities(assignedPlayers);
    auto index = _tournamentsDbContext->indexOfTournament(oldModel);
    _tournamentsDbContext->replaceTournament(index,newModel);
}

void DartsModelsService::tournamentUnAssignPlayer(const QUuid &tournamentId, const QUuid &player)
{
    auto oldModel = _getDartsTournamentByIdService->service(tournamentId,_tournamentsDbContext);;
    auto assignedPlayers = oldModel->assignedPlayerIdentities();
    assignedPlayers.removeOne(player);
    auto newModel = const_cast<IDartsTournament*>(oldModel);
    newModel->setAssignedPlayerIdentities(assignedPlayers);
    auto index = _tournamentsDbContext->indexOfTournament(oldModel);
    _tournamentsDbContext->replaceTournament(index,newModel);
}


const IDartsPointInput *DartsModelsService::setDartsPointHint(const QUuid &tournamentId,
                                                              const QUuid &playerId,
                                                              const int &round,
                                                              const int &attempt,
                                                              const int &hint)
{
    auto model = _getPointModelByParameters->getModelByParameters(_dartsPointsDb,
                                                                  tournamentId,
                                                                  playerId,
                                                                  round,
                                                                  attempt);
    auto alteredModel = _dartsPointModelHintService->service(model,hint);
    auto indexOfUnAlteredModel = _dartsPointsDb->indexOfDartsInputModel(model);
    _dartsPointsDb->replaceDartsInputModel(indexOfUnAlteredModel,alteredModel);
    return alteredModel;
}

void DartsModelsService::removePointsByTournamentId(const QUuid &tournament)
{
    auto pointModels = _getDartsPointModelsByTournamentId->service(tournament,_dartsPointsDb);
    for (auto pointModel : pointModels) {
        if(pointModel->tournamentId() == tournament)
        {
            auto index = _dartsPointsDb->indexOfDartsInputModel(pointModel);
            _dartsPointsDb->removeDartsInputModelByIndex(index);
        }
    }
}

void DartsModelsService::removePointById(const QUuid &pointId)
{
    try {
        auto scoreModel = _getDartsPointByIdService->service(pointId,_dartsPointsDb);
        auto index = _dartsPointsDb->indexOfDartsInputModel(scoreModel);
        _dartsPointsDb->removeDartsInputModelByIndex(index);
    } catch (const char *msg) {
        return;
    }
}

DartsModelsService *DartsModelsService::setGetScoreIndexesByTournamentId(GetScoreIndexesByDartsTournamentService *getScoreIndexesByTournamentId)
{
    _getScoreIndexesByTournamentId = getScoreIndexesByTournamentId;
    return this;
}

DartsModelsService *DartsModelsService::setGetDartsScoreByIdService(GetDartsScoreById *getDartsScoreById)
{
    _getDartsScoreById = getDartsScoreById;
    return this;
}

DartsModelsService *DartsModelsService::setGetDartsScoreByParametersService(IGetDartsScoreByParameters *getDartsScoreByParameters)
{
    _getDartsScoreByParameters = getDartsScoreByParameters;
    return this;
}

DartsModelsService *DartsModelsService::setGetDartsPointByIdService(GetDartsPointByIdService *getDartsPointByIdService)
{
    _getDartsPointByIdService = getDartsPointByIdService;
    return this;
}

DartsModelsService *DartsModelsService::setDartsPointModelHintService(SetDartsPointHint *dartsPointModelHintService)
{
    _dartsPointModelHintService = dartsPointModelHintService;
    return this;
}

DartsModelsService *DartsModelsService::setGetDartsPointByParametersService(IGetDartsPointByParameters *pointModelsFilterByParameters)
{
    _getPointModelByParameters = pointModelsFilterByParameters;
    return this;
}

DartsModelsService *DartsModelsService::setGetDartsPointModelsByTournamentId(GetDartsPointModelsByTournamentIdService *getDartsPointModelsByTournamentId)
{
    _getDartsPointModelsByTournamentId = getDartsPointModelsByTournamentId;
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

DartsModelsService *DartsModelsService::setGetScoreModelsByHint(GetScoreModelsByHintService *getScoreModelsByHint)
{
    _getScoreModelsByHint = getScoreModelsByHint;
    return this;
}

DartsModelsService *DartsModelsService::setDartsScoreModelHintService(SetDartsModelHint *setScoreModelHintService)
{
    _setScoreModelHintService = setScoreModelHintService;
    return this;
}

DartsModelsService* DartsModelsService::setGetScoreModelsByRoundIndex(GetScoreModelsByRoundIndex *getScoreModelsByRoundIndex)
{
    _getScoreModelsByRoundIndex = getScoreModelsByRoundIndex;
    return this;
}

DartsModelsService* DartsModelsService::setGetScoreModelsByPlayerId(GetScoreModelsByPlayerId *getScoreModelsByPlayerId)
{
    _getScoreModelsByPlayerId = getScoreModelsByPlayerId;
    return this;
}

DartsModelsService* DartsModelsService::setGetScoreModelsByTournamentId(GetScoreModelsByTournamentId *getScoreModelsByTournamentId)
{
    _getScoreModelsByTournamentId = getScoreModelsByTournamentId;
    return this;
}

DartsModelsService *DartsModelsService::setCountScoresByTournamentAndHint(CountScoresByTournamentAndHint *countScoresByTournamentAndHint)
{
    _countScoresByTournamentAndHint = countScoresByTournamentAndHint;
    return this;
}

DartsModelsService *DartsModelsService::setDartsScoresDb(IDartsScoreDb *dartsScoresDb)
{
    _dartsScoresDb = dartsScoresDb;
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

DartsModelsService *DartsModelsService::setGetOrderedDartsScoreModels(GetOrderedDartsScoreService *getOrderedDartsScoreModels)
{
    _getOrderedDartsScoreModels = getOrderedDartsScoreModels;
    return this;
}

void DartsModelsService::removePointModel(const QUuid &point)
{
    auto models = _dartsPointsDb->dartsInputModels();
    for (auto model : models) {
        auto id = model->id();
        if(id == point)
        {
            auto index = _dartsPointsDb->indexOfDartsInputModel(model);
            _dartsPointsDb->removeDartsInputModelByIndex(index);
            return;
        }
    }
}

const IDartsPointIndexes* DartsModelsService::dartsPointIndexes(const QUuid &tournamentId) const
{
    auto orderedModels = _getOrderedDartsPointsModels->service(tournamentId,_dartsPointsDb);
    auto model = _getDartsTournamentByIdService->service(tournamentId,_tournamentsDbContext);
    auto count = dartsPointsCount(tournamentId,ModelDisplayHint::DisplayHint);
    auto indexes = _assembleDartsPointIndexes->service(orderedModels,model,count);
    return indexes;
}

QVector<const IDartsPointInput *> DartsModelsService::dartsPointModelsByTournamentId(const QUuid &tournamentId) const
{
    auto models = _getDartsPointModelsByTournamentId->service(tournamentId,_dartsPointsDb);
    return models;
}

const IDartsPointInput *DartsModelsService::getDartsPointModelById(const QUuid &pointId) const
{
    auto pointModel = _getDartsPointByIdService->service(pointId,_dartsPointsDb);
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

DartsModelsService *DartsModelsService::setGetOrderedDartsPointsModels(GetOrderedDartsPointService *getOrderedDartsPointsModels)
{
    _getOrderedDartsPointsModels = getOrderedDartsPointsModels;
    return this;
}

DartsModelsService *DartsModelsService::setAssembleDartsPointIndexes(GetPointIndexesFromDartsTournamentService *getDartsPointIndexes)
{
    _assembleDartsPointIndexes = getDartsPointIndexes;
    return this;
}

int DartsModelsService::dartsPointsCount(const QUuid &tournamentId, const int &hint) const
{
    auto count = 0;
    auto models = _dartsPointsDb->dartsInputModels();
    for (auto model : models) {
        if(model->tournamentId() != tournamentId)
            continue;
        if(model->hint() == hint || hint == allHints)
            count++;
    }
    return count;
}

void DartsModelsService::addDartsPoint(const IDartsPointInput *model)
{
    _dartsPointsDb->addDartsInputModel(dynamic_cast<const IDartsPointInput*>(model));
}

QVector<const IDartsPointInput *> DartsModelsService::getDartsPointModelsOrdedByIndexes(const QUuid &tournamentId) const
{
    auto orderedModels = _getOrderedDartsPointsModels->service(tournamentId,_dartsPointsDb);
    return orderedModels;
}

void DartsModelsService::removeHiddenPoints(const QUuid &tournament)
{
    auto pointModels = _getDartsPointModelsByTournamentId->service(tournament,_dartsPointsDb);
    for (auto pointModel : pointModels)
        removePointById(pointModel->id());
}

void DartsModelsService::addDartsScore(const IDartsScoreInput* pointModel)
{
    _dartsScoresDb->addDartsInputModel(pointModel);
}

int DartsModelsService::dartsScoresCount(const int &hint) const
{
    auto count = 0;
    auto models = _dartsScoresDb->dartsScoreModels();
    for (const auto& model : models) {
        if(model->hint() == hint)
            count++;
    }
    return count;
}

const IDartsScoreInput *DartsModelsService::setDartsScoreHint(const QUuid &tournamentId,
                                                              const QUuid &playerId,
                                                              const int &roundIndex,
                                                              const int &hint)
{

    auto model = _getDartsScoreByParameters->getModelByParameters(_dartsScoresDb,tournamentId,
                                                                  playerId,roundIndex);
    auto indexOfModel = _dartsScoresDb->indexOfDartsInputModel(model);
    auto alteredModel = _setScoreModelHintService->service(model,hint);
    _dartsScoresDb->replaceDartsInputModel(indexOfModel,alteredModel);
    return alteredModel;
}

void DartsModelsService::removeScoreById(const QUuid &scoreId)
{
    auto model = _getDartsScoreById->service(scoreId,_dartsScoresDb);
    auto indexOfModel = _dartsScoresDb->indexOfDartsInputModel(model);
    _dartsScoresDb->removeDartsInputModelByIndex(indexOfModel);
}

void DartsModelsService::removeHiddenScores(const QUuid &tournamentId)
{
    auto models = _dartsScoresDb->dartsScoreModels();
    auto tournamentModels = _getScoreModelsByTournamentId->service(models,tournamentId);
    auto hiddenScoreModels = _getScoreModelsByHint->service(tournamentModels,ModelDisplayHint::HiddenHint);
    for (const auto& hiddenScoreModel : hiddenScoreModels)
        removeScoreById(hiddenScoreModel->id());
}

void DartsModelsService::removeScoresByTournamentId(const QUuid &tournamentId)
{
    auto dartsScoreModels = _dartsScoresDb->dartsScoreModels();
    auto dartsScoreModelsByTournamentId = _getScoreModelsByTournamentId->service(dartsScoreModels,tournamentId);
    for (const auto& dartsScoreModel : dartsScoreModelsByTournamentId) {
        if(dartsScoreModel->tournamentId() == tournamentId)
            removeScoreById(dartsScoreModel->id());
    }
}

void DartsModelsService::removeScoreModel(const QUuid &scoreId)
{
    auto model = _getDartsScoreById->service(scoreId,_dartsScoresDb);
    auto indexOfModel = _dartsScoresDb->indexOfDartsInputModel(model);
    _dartsScoresDb->removeDartsInputModelByIndex(indexOfModel);
}


QVector<const IDartsTournament *> DartsModelsService::dartsTournamentModels() const
{
    auto models = _tournamentsDbContext->dartsTournaments();
    return models;
}

const IDartsScoreIndexes *DartsModelsService::dartsScoreIndexes(const QUuid&tournamentId) const
{
    auto orderedModels = _getOrderedDartsScoreModels->service(tournamentId,_dartsScoresDb);
    auto model = _getDartsTournamentByIdService->service(tournamentId,_tournamentsDbContext);
    auto count = _countScoresByTournamentAndHint->service(tournamentId,
                                                          ModelDisplayHint::DisplayHint,
                                                          _dartsScoresDb);
    auto indexes = _getScoreIndexesByTournamentId->service(orderedModels,model,count);
    return indexes;
}


int DartsModelsService::dartsScoreCount(const QUuid &tournamentId, const int &hint) const
{
    auto models = _dartsScoresDb->dartsScoreModels();
    auto modelsByTournamentId = _getScoreModelsByTournamentId->service(models,tournamentId);
    auto modelsByHint = _getScoreModelsByHint->service(models,hint);
    auto count = modelsByHint.count();
    return count;
}

QVector<const IDartsScoreInput *> DartsModelsService::dartsScoreModelsByTournamentIdAndHint(const QUuid &tournamentId,
                                                                                            const int& hint) const
{
    auto models = _dartsScoresDb->dartsScoreModels();
    auto scoreModelsByTournamentId = _getScoreModelsByTournamentId->service(models,tournamentId);
    auto scoreModelsByHint = _getScoreModelsByHint->service(scoreModelsByTournamentId,hint);
    return scoreModelsByHint;
}

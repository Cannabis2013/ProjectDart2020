#include "dartspointsingleattempt.h"

using namespace DartsPointSingleAttemptContext;

void DartsPointSingleAttempt ::start()
{
    if(_currentStatus != ControllerState::Initialized &&
            _currentStatus != ControllerState::Stopped)
    {
        emit controllerIsNotInitialized();
        return;
    }
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void DartsPointSingleAttempt::stop()
{
    setCurrentStatus(ControllerState::Stopped);
    emit controllerIsStopped();
}

void DartsPointSingleAttempt::handleAndProcessUserInput(const QByteArray& json)
{
    auto dartsPointModel = _pointModelBuilderService->buildControllerPointByJson(json);
    auto dartsPointModelWithScore = _scoreCalculator->calculateScoreFromDartsPoint(dartsPointModel);
    auto setIndex = _indexController->setIndex();
    auto accumulatedScore = _scoreController->calculateAccumulatedScoreCandidate(setIndex,dartsPointModelWithScore->score());
    auto domain = _scoreEvaluator->validateInput(accumulatedScore,
                                                  dartsPointModel->modKeyCode(),
                                                  dartsPointModel->point());
    processDomain(domain,dartsPointModel->point(),accumulatedScore,dartsPointModel->modKeyCode());
}

void DartsPointSingleAttempt::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = this->tournament();
    emit sendCurrentTournamentId(tournament);
}

void DartsPointSingleAttempt::handleRequestDartsPoints()
{
    auto tournamentId = tournament();
    emit requestDartsPoints(tournamentId);
}

void DartsPointSingleAttempt::handlePointAddedToDataContext(const QByteArray &json)
{
    auto dartsPointModel = _pointModelBuilderService->buildControllerPointByJson(json);
    auto dartsPointModelWithScore = _scoreCalculator->calculateScoreFromDartsPoint(dartsPointModel);
    // Subtract score value from current user score
    _scoreController->subtractPlayerScore(dartsPointModelWithScore);
    // Sync totalturns with the current turn index
    _indexController->syncIndex();
    auto scoreValue = _scoreController->playerScore(dartsPointModel->playerId());
    _controllerModelsService->addPlayerNameToModel(dartsPointModel,currentUserName());
    _controllerModelsService->addAccumulatedScoreToModel(dartsPointModel,scoreValue);
    emit pointAddedAndPersisted(dartsPointModel->toJson());
}

DartsPointSingleAttempt *DartsPointSingleAttempt::setScoreCalculator(ScoreCalculatorService *scoreCalculator)
{
    _scoreCalculator = scoreCalculator;
    return this;
}

void DartsPointSingleAttempt::handleResetTournament()
{
    _currentStatus = ControllerState::resetState;
    _indexController->reset();
    _scoreController->resetScores();
    auto tournamentId = tournament();
    emit requestResetTournament(tournamentId);
}

void DartsPointSingleAttempt::sendCurrentTurnValues()
{
    auto turnValues = _dartsTurnValuesBuilderService->service(_indexController,
                                                             _scoreController,
                                                             _pointLogisticInterface);
    emit isReadyAndAwaitsInput(turnValues->toJson());
}

QString DartsPointSingleAttempt::currentUserName()
{
    auto index = _indexController->setIndex();
    auto playerName = _scoreController->playerNameByIndex(index);
    return playerName;
}

QUuid DartsPointSingleAttempt::currentPlayerId()
{
    auto index = _indexController->setIndex();
    auto playerID = _scoreController->playerIdAtIndex(index);
    return playerID;
}

QUuid DartsPointSingleAttempt::tournament()
{
    return _tournament;
}

int DartsPointSingleAttempt::status()
{
    return _currentStatus;
}

int DartsPointSingleAttempt::lastPlayerIndex()
{
    auto playerCount = _scoreController->playersCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid DartsPointSingleAttempt::undoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return QUuid();
    _currentStatus = ControllerState::UndoState;
    _indexController->undo();
    auto roundIndex = _indexController->roundIndex();
    auto attemptIndex = _indexController->attemptIndex();
    emit hideDartsPoint(tournament(),
                        currentPlayerId(),
                        roundIndex,
                        attemptIndex);
    auto playerId = currentPlayerId();
    return playerId;
}

QUuid DartsPointSingleAttempt::redoTurn()
{
    setCurrentStatus(ControllerState::RedoState);
    auto activeUser = currentPlayerId();
    auto roundIndex = _indexController->roundIndex();
    auto throwIndex = _indexController->attemptIndex();
    _indexController->redo();
    emit revealDartsPoint(tournament(),
                               activeUser,
                               roundIndex,
                               throwIndex);
    auto index = _indexController->setIndex();
    auto playerId = _scoreController->playerIdAtIndex(index);
    return playerId;
}

void DartsPointSingleAttempt::addPoint(const int& point,
                                       const int& score,
                                       const int& keyCode)
{
    if(currentStatus() != ControllerState::WinnerDeclared)
        setCurrentStatus(ControllerState::AddScoreState);
    auto pointModel = _pointModelBuilderService->buildControllerPointByInputValues(point,score,keyCode);
    _controllerModelsService->addPlayerNameToModel(pointModel,currentUserName());
    _controllerModelsService->addPlayerIdToModel(pointModel,currentPlayerId());
    _controllerModelsService->addTournamentIdToModel(pointModel,tournament());
    auto indexes = _dartsIndexesBuilderService->buildControllerIndexesByIndexService(_indexController);
    auto json = _dartsJsonService->buildJsonByIndexesAndPoint(indexes,pointModel);
    emit requestAddDartsPoint(json);
}

void DartsPointSingleAttempt::handleRequestFromUI()
{
    if(status() == ControllerState::Initialized)
    {
        emit controllerIsInitializedAndReady();
    }
    else if(status() == ControllerState::AddScoreState)
    {
        nextTurn();
    }
    else if(status() == ControllerState::UndoState)
    {
        setCurrentStatus(ControllerState::AwaitsInput);
        sendCurrentTurnValues();
    }
    else if(status() == ControllerState::RedoState)
    {
        setCurrentStatus(ControllerState::AwaitsInput);
        sendCurrentTurnValues();
    }
    else if(status() == ControllerState::WinnerDeclared)
    {
        auto winnerName = _scoreController->winnerUserName();
        auto json = _dartsJsonService->assembleJsonWinnerName(winnerName);
        emit winnerDeclared(json);
    }
    else if(status() == ControllerState::resetState)
    {
        setCurrentStatus(ControllerState::Initialized);
        emit dartsSingleAttemptControllerIsInitialized();
    }
}

void DartsPointSingleAttempt::nextTurn()
{
    _indexController->next();
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void DartsPointSingleAttempt::declareWinner()
{
    auto index = _indexController->setIndex();
    auto currentPlayerId = _scoreController->playerIdAtIndex(index);
    _scoreController->setWinner(currentPlayerId);
    setCurrentStatus(ControllerState::WinnerDeclared);
}

DartsPointSingleAttempt *DartsPointSingleAttempt::setPlayerModelBuilderService(PlayerModelBuilder *newPlayerModelBuilderService)
{
    _playerModelBuilderService = newPlayerModelBuilderService;
    return this;
}

DartsPointSingleAttempt *DartsPointSingleAttempt::setControllerModelsService(ControllerModelsService *newControllerModelsService)
{
    _controllerModelsService = newControllerModelsService;
    return this;
}

DartsPointSingleAttempt *DartsPointSingleAttempt::setBuildDartsIndexesByJson(IIndexesBuilderService *newBuildDartsIndexesByJson)
{
    _dartsIndexesBuilderService = newBuildDartsIndexesByJson;
    return this;
}

DartsPointSingleAttempt *DartsPointSingleAttempt::setDartsPointBuilderService(ControllerPointBuilder *newDartsPointBuilderService)
{
    _pointModelBuilderService = newDartsPointBuilderService;
    return this;
}

DartsPointSingleAttempt *DartsPointSingleAttempt::setAssembleDartsPointTurnValues(TurnValueBuilderService *newAssembleDartsPointTurnValues)
{
    _dartsTurnValuesBuilderService = newAssembleDartsPointTurnValues;
    return this;
}

DartsPointSingleAttempt* DartsPointSingleAttempt::setDartsJsonModelsService(DartsJsonService *dartsJsonModelsService)
{
    _dartsJsonService = dartsJsonModelsService;
    return this;
}

int DartsPointSingleAttempt::currentStatus() const
{
    return _currentStatus;
}

void DartsPointSingleAttempt::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = _dartsIndexesBuilderService->buildControllerIndexesByJson(json);
    _indexController->setIndexes(indexes);
    emit requestTournamentAssignedPlayerDetails(tournament());
}

void DartsPointSingleAttempt::processDomain(const int& domain,
                                            const int& point,
                                            const int& score,
                                            const int& modKeyCode)
{
    switch (domain)
    {
        // In case user enters scores above 180
        case OutOfRange : sendCurrentTurnValues();break;
        case PointDomain : addPoint(point,score,modKeyCode);break;
        case CriticalDomain : addPoint(point,score,modKeyCode);break;
        case TargetDomain : {
            declareWinner();
            addPoint(point,score,modKeyCode);
            break;
        }
        case OutsideDomain : addPoint(0,0,modKeyCode);break;
    }
}

DartsPointSingleAttempt* DartsPointSingleAttempt::setInputController(PlayerPointService *scoreController)
{
    _scoreController = scoreController;
    return this;
}

DartsPointSingleAttempt* DartsPointSingleAttempt::setIndexController(DartsIndexService *indexController)
{
    _indexController = indexController;
    return this;
}

DartsPointSingleAttempt *DartsPointSingleAttempt::setInputValidator(IPointValidator *scoreEvaluator)
{
    _scoreEvaluator = scoreEvaluator;
    return this;
}

void DartsPointSingleAttempt::setCurrentStatus(int currentStatus)
{
    _currentStatus = currentStatus;
}

DartsPointSingleAttempt *DartsPointSingleAttempt::createInstance(const QUuid &tournament)
{
    return new DartsPointSingleAttempt(tournament);
}

IDartsLogisticsService<QString> *DartsPointSingleAttempt::pointLogisticInterface() const
{
    return _pointLogisticInterface;
}

DartsPointSingleAttempt *DartsPointSingleAttempt::setLogisticInterface(IDartsLogisticsService<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void DartsPointSingleAttempt::beginInitialize()
{
    auto tournamentId = tournament();
    emit requestDartsTournamentIndexes(tournamentId);
}

void DartsPointSingleAttempt::undoSuccess(const QByteArray& json)
{
    auto dartsPointModel = _pointModelBuilderService->buildControllerPointByJson(json);
    auto dartsPointModelWithScore = _scoreCalculator->calculateScoreFromDartsPoint(dartsPointModel);
    _scoreController->addPlayerScore(dartsPointModelWithScore);
    auto newScore = _scoreController->playerScore(dartsPointModel->playerId());
    auto playerName = _scoreController->playerNameById(dartsPointModel->playerId());
    _controllerModelsService->addPlayerNameToModel(dartsPointModel,playerName);
    _controllerModelsService->addAccumulatedScoreToModel(dartsPointModel,newScore);
    emit pointRemoved(dartsPointModel->toJson());
}

void DartsPointSingleAttempt::redoSuccess(const QByteArray& json)
{
    auto dartsPointModel = _pointModelBuilderService->buildControllerPointByJson(json);
    auto dartsPointModelWithScore = _scoreCalculator->calculateScoreFromDartsPoint(dartsPointModel);
    _scoreController->subtractPlayerScore(dartsPointModelWithScore);
    auto newScore = _scoreController->playerScore(dartsPointModelWithScore->playerId());
    auto playerName = _scoreController->playerNameById(dartsPointModelWithScore->playerId());
    _controllerModelsService->addPlayerNameToModel(dartsPointModelWithScore,playerName);
    _controllerModelsService->addAccumulatedScoreToModel(dartsPointModelWithScore,newScore);
    emit pointAddedAndPersisted(dartsPointModelWithScore->toJson());
}


void DartsPointSingleAttempt::initializeControllerPlayerDetails(const QByteArray& json)
{
    auto playerModels = _playerModelBuilderService->buildPlayerModelsByJson(json);
    _indexController->setPlayersCount(playerModels.count());
    _scoreController->addPlayerEntitiesByModels(playerModels);
    emit requestTournamentDartsPoints(tournament());
}

void DartsPointSingleAttempt::initializeControllerDartsPoints(const QByteArray& json)
{
    auto points = _pointModelBuilderService->buildControllerPointsByJson(json);
    _scoreCalculator->addCalculatedScoreToDartsPoints(points);
    _scoreController->subtractPlayerScoresByModels(points);
    emit requestTournamentWinnerIdAndName(tournament());
}

void DartsPointSingleAttempt::initializeControllerWinnerIdAndName(const QByteArray& json)
{
    auto winnerId = _dartsJsonService->getWinnerIdByJson(json);
    _scoreController->setWinner(winnerId);
    if(_scoreController->winnerId() != QUuid())
        setCurrentStatus(ControllerState::WinnerDeclared);
    else
        setCurrentStatus(ControllerState::Initialized);
    emit dartsSingleAttemptControllerIsInitialized();
}

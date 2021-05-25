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
    auto controllerPoint = _controllerPointBuilderService->service(json);
    auto score = _scoreCalculator->calculateScoreFromDartsPoint(controllerPoint->point(),
                                                                 controllerPoint->modKeyCode());
    auto setIndex = _indexController->setIndex();
    auto accumulatedScore = _scoreController->calculateAccumulatedScoreCandidate(setIndex,score);
    auto domain = _scoreEvaluator->validateInput(accumulatedScore,
                                                  controllerPoint->modKeyCode(),
                                                  controllerPoint->point());
    processDomain(domain,controllerPoint->point(),accumulatedScore,controllerPoint->modKeyCode());
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
    auto dartsPointModel = _controllerPointBuilderService->service(json);
    auto score = _scoreCalculator->calculateScoreFromDartsPoint(dartsPointModel->point(),
                                                                dartsPointModel->modKeyCode());
    // Subtract score value from current user score
    _scoreController->subtractPlayerScore(dartsPointModel->playerId(),score);
    // Sync totalturns with the current turn index
    _indexController->syncIndex();
    auto scoreValue = _scoreController->playerScore(dartsPointModel->playerId());
    _addPlayerNameToPointService->service(currentActiveUser(),dartsPointModel);
    _addPlayerScoreToPointService->service(scoreValue,dartsPointModel);
    emit pointAddedAndPersisted(dartsPointModel->toJson());
}

DartsPointSingleAttempt *DartsPointSingleAttempt::setScoreCalculator(IPointCalculatorService *scoreCalculator)
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
    auto turnValues = _assembleDartsPointTurnValues->service(_indexController,
                                                        _scoreController,
                                                        _pointLogisticInterface);
    emit isReadyAndAwaitsInput(turnValues->toJson());
}

QString DartsPointSingleAttempt::currentActiveUser()
{
    auto index = _indexController->setIndex();
    auto playerName = _scoreController->playerNameByIndex(index);
    return playerName;
}

QUuid DartsPointSingleAttempt::currentActivePlayerId()
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
    auto throwIndex = _indexController->attemptIndex();
    emit hideDartsPoint(tournament(),
                        currentActivePlayerId(),
                        roundIndex,
                        throwIndex);
    auto playerId = currentActivePlayerId();
    return playerId;
}

QUuid DartsPointSingleAttempt::redoTurn()
{
    setCurrentStatus(ControllerState::RedoState);
    auto activeUser = currentActivePlayerId();
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
    // Set controller state, unless winner declared
    if(currentStatus() != ControllerState::WinnerDeclared)
        setCurrentStatus(ControllerState::AddScoreState);
    auto winnerId = status() == ControllerState::WinnerDeclared ?
                currentActivePlayerId() : QUuid();
    auto json = _dartsJsonModelsService->assembleJsonAddPointValues(
                tournament(),
                _indexController->roundIndex(),
                _indexController->setIndex(),
                _indexController->attemptIndex(),
                winnerId,currentActivePlayerId(),
                point,score,keyCode);
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
        /*
         * - Increment indexes
         * - Notify datacontext to create models if necessary
         * - Datacontext responds with a signal which is handled in 'handleReplyFromDataContext' slot
         * - Otherwise, it just emits a signal with current round values
         */
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
        auto json = _dartsJsonModelsService->assembleJsonWinnerName(winnerName);
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

DartsPointSingleAttempt *DartsPointSingleAttempt::setBuildDartsIndexesByJson(IBuildIndexesService *newBuildDartsIndexesByJson)
{
    _buildDartsIndexesByJson = newBuildDartsIndexesByJson;
    return this;
}

DartsPointSingleAttempt *DartsPointSingleAttempt::setAddPlayerScoreToPointService(IAddPlayerScoreService *newAddPlayerScoreToPointService)
{
    _addPlayerScoreToPointService = newAddPlayerScoreToPointService;
    return this;
}

DartsPointSingleAttempt *DartsPointSingleAttempt::setAddPlayerNameToPointService(IAddPlayerNameService *newAddPlayerNameToPointService)
{
    _addPlayerNameToPointService = newAddPlayerNameToPointService;
    return this;
}

DartsPointSingleAttempt *DartsPointSingleAttempt::setDartsPointBuilderService(IControllerPointBuilder *newDartsPointBuilderService)
{
    _controllerPointBuilderService = newDartsPointBuilderService;
    return this;
}

DartsPointSingleAttempt *DartsPointSingleAttempt::setAssembleDartsPointTurnValues(TurnValueBuilderService *newAssembleDartsPointTurnValues)
{
    _assembleDartsPointTurnValues = newAssembleDartsPointTurnValues;
    return this;
}

DartsPointSingleAttempt* DartsPointSingleAttempt::setDartsJsonModelsService(DartsJsonService *dartsJsonModelsService)
{
    _dartsJsonModelsService = dartsJsonModelsService;
    return this;
}

int DartsPointSingleAttempt::currentStatus() const
{
    return _currentStatus;
}

void DartsPointSingleAttempt::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = _buildDartsIndexesByJson->service(json);
    _indexController->setIndexes(indexes);
    emit requestTournamentAssignedPlayerDetails(tournament());
}

bool DartsPointSingleAttempt::isBusy()
{
    if(status() == Stopped ||
            status() == WinnerDeclared)
    {
        emit controllerIsStopped();
        return true;
    }
    else if(status() == ControllerState::AddScoreState)
    {
        return true;
    }
    return false;
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

DartsPointSingleAttempt* DartsPointSingleAttempt::setInputController(IPlayerPointService *scoreController)
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
    auto controllerPoint = _controllerPointBuilderService->service(json);
    auto score = _scoreCalculator->calculateScoreFromDartsPoint(controllerPoint->point(),controllerPoint->modKeyCode());
    _scoreController->addPlayerScore(controllerPoint->playerId(),score);
    auto newScore = _scoreController->playerScore(controllerPoint->playerId());
    auto playerName = _scoreController->playerNameById(controllerPoint->playerId());
    _addPlayerNameToPointService->service(playerName,controllerPoint);
    _addPlayerScoreToPointService->service(newScore,controllerPoint);
    emit pointRemoved(controllerPoint->toJson());
}

void DartsPointSingleAttempt::redoSuccess(const QByteArray& json)
{
    auto controllerPoint = _controllerPointBuilderService->service(json);
    auto score = _scoreCalculator->calculateScoreFromDartsPoint(controllerPoint->point(),controllerPoint->modKeyCode());
    _scoreController->subtractPlayerScore(controllerPoint->playerId(),score);
    auto newScore = _scoreController->playerScore(controllerPoint->playerId());
    auto playerName = _scoreController->playerNameById(controllerPoint->playerId());
    _addPlayerNameToPointService->service(playerName,controllerPoint);
    _addPlayerScoreToPointService->service(newScore,controllerPoint);
    emit pointAddedAndPersisted(controllerPoint->toJson());
}


void DartsPointSingleAttempt::initializeControllerPlayerDetails(const QByteArray& json)
{
    auto playerStructs = _dartsJsonModelsService->assemblePlayerDetailsStructsFromJson(json);
    _indexController->setPlayersCount(playerStructs.count());
    for (const auto &playerStruct : playerStructs)
        _scoreController->addPlayerEntity(playerStruct->playerId,playerStruct->playerName);
    emit requestTournamentDartsPoints(tournament());
}

void DartsPointSingleAttempt::initializeControllerDartsPoints(const QByteArray& json)
{
    auto extendedPointStructs = _dartsJsonModelsService->
            assembleExtendedInputModelsFromJson(json);
    for (const auto &extendedPointStruct : extendedPointStructs) {
        auto calculatedScore = _scoreCalculator->
                calculateScoreFromDartsPoint(extendedPointStruct->pointValue,
                                             extendedPointStruct->modKeyCode);
        _scoreController->subtractPlayerScore(extendedPointStruct->playerId,
                                              calculatedScore);
    }
    emit requestTournamentWinnerIdAndName(tournament());
}

void DartsPointSingleAttempt::initializeControllerWinnerIdAndName(const QByteArray& json)
{
    auto winnerStruct = _dartsJsonModelsService->assembleWinnerStructFromJson(json);
    _scoreController->setWinner(winnerStruct->playerId);
    if(_scoreController->winnerId() != QUuid())
        setCurrentStatus(ControllerState::WinnerDeclared);
    else
        setCurrentStatus(ControllerState::Initialized);
    emit dartsSingleAttemptControllerIsInitialized();
}

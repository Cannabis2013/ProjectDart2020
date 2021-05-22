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
    auto pointStruct = DartsPoint::fromJson(json);
    // Check for status
    if(isBusy()) return;
    // Calculate score
    auto score = _scoreCalculator->calculateScoreFromDartsPoint(pointStruct->point(),
                                                                 pointStruct->modKeyCode());
    auto setIndex = _indexController->setIndex();
    auto accumulatedScore = _scoreController->calculateAccumulatedScoreCandidate(setIndex,score);
    // Evaluate input according to point domain and aggregated sum domain
    auto domain = _scoreEvaluator->validateInput(accumulatedScore,
                                                  pointStruct->modKeyCode(),
                                                  pointStruct->point());
    /*
     * - Check domain value
     * - Add or nullify point
     */
    processDomain(domain,pointStruct->point(),accumulatedScore,pointStruct->modKeyCode());
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
    auto dartsPointModel = DartsPoint::fromJson(json);
    auto score = _scoreCalculator->calculateScoreFromDartsPoint(dartsPointModel->point(),
                                                                dartsPointModel->modKeyCode());
    // Subtract score value from current user score
    _scoreController->subtractPlayerScore(dartsPointModel->playerId(),score);
    // Sync totalturns with the current turn index
    _indexController->syncIndex();
    auto scoreValue = _scoreController->playerScore(dartsPointModel->playerId());
    dartsPointModel->setPlayerName(currentActiveUser());
    dartsPointModel->setAccumulatedScore(scoreValue);
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
    auto playerName = _scoreController->playerNameById(currentActivePlayerId());
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

DartsPointSingleAttempt *DartsPointSingleAttempt::setAssembleDartsPointTurnValues(TurnValueBuilderService *newAssembleDartsPointTurnValues)
{
    _assembleDartsPointTurnValues = newAssembleDartsPointTurnValues;
    return this;
}

DartsPointSingleAttempt* DartsPointSingleAttempt::setDartsJsonModelsService(IDartsSingleAttemptPointJsonService *dartsJsonModelsService)
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
    auto indexes = _dartsJsonModelsService->assembleDartsIndexesFromJson(json);
    _indexController->setIndexes(indexes->totalTurns,indexes->turns,indexes->roundIndex,
                                 indexes->setIndex,indexes->attemptIndex);
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

DartsPointSingleAttempt* DartsPointSingleAttempt::setIndexController(IDartsSingleAttemptIndexService *indexController)
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
    auto pointStruct = _dartsJsonModelsService->assembleExtendedInputModelFromJson(json);
    auto score = _scoreCalculator->calculateScoreFromDartsPoint(pointStruct->pointValue,pointStruct->modKeyCode);
    _scoreController->addPlayerScore(pointStruct->playerId,score);
    auto newScore = _scoreController->playerScore(pointStruct->playerId);
    auto playerName = _scoreController->playerNameById(pointStruct->playerId);
    auto data = _dartsJsonModelsService->assembleJsonFromParameters(playerName,pointStruct->pointValue,newScore);
    emit pointRemoved(data);
}

void DartsPointSingleAttempt::redoSuccess(const QByteArray& json)
{
    auto pointStruct = _dartsJsonModelsService->assembleExtendedInputModelFromJson(json);
    auto score = _scoreCalculator->calculateScoreFromDartsPoint(pointStruct->pointValue,pointStruct->modKeyCode);
    _scoreController->subtractPlayerScore(pointStruct->playerId,score);
    auto newScore = _scoreController->playerScore(pointStruct->playerId);
    auto playerName = _scoreController->playerNameById(pointStruct->playerId);
    auto data = _dartsJsonModelsService->assembleJsonFromParameters(playerName,pointStruct->pointValue,
                                                                    newScore,pointStruct->modKeyCode);
    emit pointAddedAndPersisted(data);
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

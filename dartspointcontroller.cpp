#include "dartspointcontroller.h"

void DartsPointController ::start()
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

void DartsPointController::stop()
{
    setCurrentStatus(ControllerState::Stopped);
    emit controllerIsStopped();
}

void DartsPointController::handleAndProcessUserInput(const QByteArray& json)
{
    auto pointStruct = _dartsJsonModelsService->assemblePointStructFromJson(json);
    // Check for status
    if(isBusy()) return;
    // Calculate score
    auto score = _scoreCalculator->calculateScoreFromDartsPoint(pointStruct->pointValue,
                                                                 pointStruct->modKeyCode);
    auto setIndex = _indexController->setIndex();
    auto accumulatedScore = _scoreController->calculateAccumulatedScoreCandidate(setIndex,score);
    // Evaluate input according to point domain and aggregated sum domain
    auto domain = _scoreEvaluator->validateInput(accumulatedScore,
                                                  pointStruct->modKeyCode,
                                                  pointStruct->pointValue);
    /*
     * - Check domain value
     * - Add or nullify point
     */
    processDomain(domain,pointStruct->pointValue,pointStruct->modKeyCode);
}

void DartsPointController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = this->tournament();
    emit sendCurrentTournamentId(tournament);
}

void DartsPointController::assembleSingleAttemptDartsPoints()
{
    auto json = _dartsJsonModelsService->assembleJsonDartsPoints(_scoreController);
    emit sendSingleAttemptDartsPoints(json);
}

void DartsPointController::handleRequestDartsPoints()
{
    auto tournamentId = tournament();
    emit requestDartsPoints(tournamentId);
}

void DartsPointController::handlePointAddedToDataContext(const QByteArray &json)
{
    auto pointStruct = _dartsJsonModelsService->assembleExtendedInputModelFromJson(json);
    auto score = _scoreCalculator->calculateScoreFromDartsPoint(pointStruct->pointValue,pointStruct->modKeyCode);
    // Subtract score value from current user score
    _scoreController->subtractPlayerScore(pointStruct->playerId,score);
    // Sync totalturns with the current turn index
    _indexController->syncIndex();
    auto scoreValue = _scoreController->userScore(pointStruct->playerId);
    auto newJson = _dartsJsonModelsService->assembleJsonDartsPoint(currentActiveUser(),pointStruct->pointValue,scoreValue);
    emit pointAddedAndPersisted(newJson);
}

DartsPointController *DartsPointController::setScoreCalculator(ScoreCalculatorInterface *scoreCalculator)
{
    _scoreCalculator = scoreCalculator;
    return this;
}

void DartsPointController::handleResetTournament()
{
    _currentStatus = ControllerState::resetState;
    _indexController->reset();
    _scoreController->resetScores();
    auto tournamentId = tournament();
    emit requestResetTournament(tournamentId);
}

void DartsPointController::sendCurrentTurnValues()
{
    auto canUndo = _indexController->canUndo();
    auto canRedo = _indexController->canRedo();
    auto roundIndex = _indexController->roundIndex();
    auto setIndex = _indexController->setIndex();
    auto score = _scoreController->userScore(setIndex);;
    auto attemptIndex = _indexController->attempt() + 1;
    QString targetRow = "Logistic controller not injected!";
    if(_pointLogisticInterface != nullptr)
        targetRow = pointLogisticInterface()->suggestTargetRow(score,attemptIndex);
    auto data = _dartsJsonModelsService->assembleJsonTurnValues(canUndo,canRedo,roundIndex,currentActiveUser(),targetRow);
    emit isReadyAndAwaitsInput(data);
}

QString DartsPointController::currentActiveUser()
{
    auto index = _indexController->setIndex();
    auto playerName = _scoreController->userNameAtIndex(index);
    return playerName;
}

QUuid DartsPointController::currentActivePlayerId()
{
    auto index = _indexController->setIndex();
    auto playerID = _scoreController->userIdAtIndex(index);
    return playerID;
}

QUuid DartsPointController::tournament()
{
    return _tournament;
}

int DartsPointController::status()
{
    return _currentStatus;
}

int DartsPointController::lastPlayerIndex()
{
    auto playerCount = _scoreController->playersCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid DartsPointController::undoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return QUuid();
    _currentStatus = ControllerState::UndoState;
    _indexController->undo();
    auto roundIndex = _indexController->roundIndex();
    auto throwIndex = _indexController->attempt();
    emit hideDartsPoint(tournament(),
                             currentActivePlayerId(),
                             roundIndex,
                             throwIndex);
    auto playerId = currentActivePlayerId();
    return playerId;
}

QUuid DartsPointController::redoTurn()
{
    setCurrentStatus(ControllerState::RedoState);
    auto activeUser = currentActivePlayerId();
    auto roundIndex = _indexController->roundIndex();
    auto throwIndex = _indexController->attempt();
    _indexController->redo();
    emit revealDartsInputPoint(tournament(),
                               activeUser,
                               roundIndex,
                               throwIndex);
    auto index = _indexController->setIndex();
    auto playerId = _scoreController->userIdAtIndex(index);
    return playerId;
}

void DartsPointController::addPoint(const int& point,
                                    const int& keyCode)
{
    // Set controller state, unless winner declared
    if(currentStatus() != ControllerState::WinnerDeclared)
        setCurrentStatus(ControllerState::AddScoreState);
    auto winnerId = status() == ControllerState::WinnerDeclared ? currentActivePlayerId() : "";
    auto json = _dartsJsonModelsService->assembleJsonAddPointValues(tournament(),_indexController->roundIndex(),
                                                                    _indexController->setIndex(),_indexController->attempt(),
                                                                    winnerId,currentActivePlayerId(),point,keyCode);
    emit requestAddDartsPoint (json);
}

void DartsPointController::handleRequestFromUI()
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
        emit controllerIsInitialized();
    }
}

void DartsPointController::nextTurn()
{
    _indexController->next();
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void DartsPointController::declareWinner()
{
    auto index = _indexController->setIndex();
    auto currentPlayerId = _scoreController->userIdAtIndex(index);
    _scoreController->setWinner(currentPlayerId);
    setCurrentStatus(ControllerState::WinnerDeclared);
}

DartsPointController* DartsPointController::setDartsJsonModelsService(IDartsSingleAttemptPointJsonService *dartsJsonModelsService)
{
    _dartsJsonModelsService = dartsJsonModelsService;
    return this;
}

int DartsPointController::currentStatus() const
{
    return _currentStatus;
}

void DartsPointController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = _dartsJsonModelsService->assembleDartsIndexesFromJson(json);
    _indexController->setIndexes(indexes->totalTurns,indexes->turns,indexes->roundIndex,
                                 indexes->setIndex,indexes->attemptIndex);
    emit requestTournamentAssignedPlayerDetails(tournament());
}

bool DartsPointController::isBusy()
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

void DartsPointController::processDomain(const int& domain,
                                       const int& point,
                                       const int& modKeyCode)
{
    switch (domain)
    {
        // In case user enters scores above 180
        case OutOfRange : sendCurrentTurnValues();break;
        case PointDomain : addPoint(point,modKeyCode);break;
        case CriticalDomain : addPoint(point,modKeyCode);break;
        case TargetDomain : {
            declareWinner();
            addPoint(point,modKeyCode);
            break;
        }
        case OutsideDomain : addPoint(0,modKeyCode);break;
    }
}

DartsPointController* DartsPointController::setScoreController(IScoreController *scoreController)
{
    _scoreController = scoreController;
    return this;
}

DartsPointController* DartsPointController::setIndexController(IndexControllerInterface *indexController)
{
    _indexController = indexController;
    return this;
}

DartsPointController *DartsPointController::setInputValidator(IPointValidator *scoreEvaluator)
{
    _scoreEvaluator = scoreEvaluator;
    return this;
}

void DartsPointController::setCurrentStatus(int currentStatus)
{
    _currentStatus = currentStatus;
}

DartsPointController *DartsPointController::createInstance(const QUuid &tournament)
{
    return new DartsPointController(tournament);
}

FTPLogisticControllerInterface<QString> *DartsPointController::pointLogisticInterface() const
{
    return _pointLogisticInterface;
}

DartsPointController *DartsPointController::setLogisticInterface(FTPLogisticControllerInterface<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void DartsPointController::beginInitialize()
{
    auto tournamentId = tournament();
    emit requestDartsTournamentIndexes(tournamentId);
}

void DartsPointController::undoSuccess(const QByteArray& json)
{
    auto pointStruct = _dartsJsonModelsService->assembleExtendedInputModelFromJson(json);
    auto score = _scoreCalculator->calculateScoreFromDartsPoint(pointStruct->pointValue,pointStruct->modKeyCode);
    _scoreController->addPlayerScore(pointStruct->playerId,score);
    auto newScore = _scoreController->userScore(pointStruct->playerId);
    auto playerName = _scoreController->userNameFromId(pointStruct->playerId);
    auto data = _dartsJsonModelsService->assembleJsonFromParameters(playerName,pointStruct->pointValue,newScore);
    emit pointRemoved(data);
}

void DartsPointController::redoSuccess(const QByteArray& json)
{
    auto pointStruct = _dartsJsonModelsService->assembleExtendedInputModelFromJson(json);
    auto score = _scoreCalculator->calculateScoreFromDartsPoint(pointStruct->pointValue,pointStruct->modKeyCode);
    _scoreController->subtractPlayerScore(pointStruct->playerId,score);
    auto newScore = _scoreController->userScore(pointStruct->playerId);
    auto playerName = _scoreController->userNameFromId(pointStruct->playerId);
    auto data = _dartsJsonModelsService->assembleJsonFromParameters(playerName,pointStruct->pointValue,
                                                                    newScore,pointStruct->modKeyCode);
    emit pointAddedAndPersisted(data);
}


void DartsPointController::initializeControllerPlayerDetails(const QByteArray& json)
{
    auto playerStructs = _dartsJsonModelsService->assemblePlayerDetailsStructsFromJson(json);
    _indexController->setPlayersCount(playerStructs.count());
    for (const auto &playerStruct : playerStructs)
        _scoreController->addPlayerEntity(playerStruct->playerId,playerStruct->playerName);
    emit requestTournamentDartsPoints(tournament());
}

void DartsPointController::initializeControllerDartsPoints(const QByteArray& json)
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

void DartsPointController::initializeControllerWinnerIdAndName(const QByteArray& json)
{
    auto winnerStruct = _dartsJsonModelsService->assembleWinnerStructFromJson(json);
    _scoreController->setWinner(winnerStruct->playerId);
    if(_scoreController->winnerId() != QUuid())
        setCurrentStatus(ControllerState::WinnerDeclared);
    else
        setCurrentStatus(ControllerState::Initialized);
    emit controllerIsInitialized();
}

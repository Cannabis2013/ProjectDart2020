#include "localftpcontroller.h"

void LocalFTPController::start()
{
    if(_currentStatus != ControllerState::Initialized &&
            _currentStatus != ControllerState::Stopped)
    {
        emit transmitResponse(ControllerState::NotInitialized,{});
        return;
    }
    _isActive = true;
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void LocalFTPController::stop()
{
    _isActive = false;
    _currentStatus = ControllerState::Stopped;
    emit transmitResponse(ControllerResponse::isStopped,{});
}

void LocalFTPController::handleAndProcessUserInput(const int &point,
                                              const int &modifierKeyCode)
{
    // Check for status
    if(status() == Stopped ||
            status() == WinnerDeclared)
    {
        emit transmitResponse(ControllerResponse::isStopped,{});
        return;
    }
    else if(status() == ControllerState::AddScoreState)
    {
        emit transmitResponse(ControllerResponse::isProcessingUserInput,{});
        return;
    }
    // Set controller state
    _currentStatus = ControllerState::AddScoreState;
    // Calculate score
    auto score = scoreCalculator()->calculateScore(point,modifierKeyCode);
    auto setIndex = indexController()->setIndex();
    auto currentScore = scoreController()->scoreAtIndex(setIndex);;
    auto newScore = currentScore - score;

    // Evaluate input according to point domain and aggregated sum domain
    auto domain = scoreEvaluator()->validateInput(newScore,modifierKeyCode,point);
    switch (domain)
    {
        // In case user enters scores above 180
        case InputValidatorInterface::InputOutOfRange : sendCurrentTurnValues(); break;
        case InputValidatorInterface::PointDomain : addPoint(score,newScore);break;
        case InputValidatorInterface::CriticalDomain : addPoint(score,newScore);break;
        case InputValidatorInterface::TargetDomain : {
            declareWinner();
            addPoint(score,newScore);
            break;
        }
        case InputValidatorInterface::OutsideDomain : addPoint(0,currentScore);break;
    }
}

void LocalFTPController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = this->tournament();
    emit requestTournamentMetaData(tournament);
}

void LocalFTPController::handleRequestForPlayerScores()
{
    auto tournamentId = tournament();
    QList<QUuid> playerIds;
    QList<QString> playerNames;
    auto count = scoreController()->userScoresCount();
    for (int i = 0; i < count; ++i) {
        playerIds += scoreController()->userIdAtIndex(i);
        playerNames += scoreController()->userNameAtIndex(i);

    }
    emit sendAssignedTournamentPlayers(tournamentId,playerIds,playerNames);
}

void LocalFTPController::handleScoreAddedToDataContext(const QUuid &playerID,
                                                            const int &point,
                                                            const int &score)
{
    scoreController()->setScoreAtId(playerID,score);
    auto playerName = scoreController()->userNameFromId(playerID);
    indexController()->syncIndex();
    emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,point,score});
}

void LocalFTPController::handleDataContextUpdated()
{
    _currentStatus = ControllerState::AwaitsInput;
    sendCurrentTurnValues();
}

void LocalFTPController::handleScoreHintUpdated(const QUuid &playerID,
                                                     const int &point,
                                                     const int &score)
{
    if(status() == ControllerState::UndoState)
    {
        auto newScore = score + point;
        scoreController()->setScoreAtId(playerID,newScore);
        auto playerName = scoreController()->userNameFromId(playerID);
        emit transmitResponse(ControllerResponse::ScoreRemove,
                              {playerName,newScore,point});
    }
    else if(status() == ControllerState::RedoState)
    {
        scoreController()->setScoreAtId(playerID,score);
        auto playerName = scoreController()->userNameFromId(playerID);
        emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,point,score});
    }
}

void LocalFTPController::handleTournamentResetSuccess()
{
    // Reset index controller
    indexController()->reset();
    emit transmitResponse(ControllerResponse::transmitInitialScore,{});

}

ScoreCalculatorInterface *LocalFTPController::scoreCalculator() const
{
    return _scoreCalculatorService;
}

LocalFTPController *LocalFTPController::setScoreCalculator(ScoreCalculatorInterface *service)
{
    _scoreCalculatorService = service;
    return this;
}

void LocalFTPController::handleResetTournament()
{
    _currentStatus = ControllerState::resetState;
    emit requestResetTournament(tournament());
}

void LocalFTPController::sendCurrentTurnValues()
{
    auto canUndo = indexController()->canUndo();
    auto canRedo = indexController()->canRedo();
    auto roundIndex = indexController()->roundIndex();
    auto currentUserName = currentActiveUser();
    auto setIndex = indexController()->setIndex();
    auto score = scoreController()->scoreAtIndex(setIndex);;
    auto throwIndex = indexController()->legIndex() + 1;
    auto throwSuggestion = pointLogisticInterface()->throwSuggestion(score,throwIndex);
    QVariantList responseParameters = {
        canUndo,
        canRedo,
        roundIndex,
        currentUserName,
        throwSuggestion
    };
    emit transmitResponse(ControllerResponse::initializedAndAwaitsInput,
                          responseParameters);
}

QString LocalFTPController::currentActiveUser()
{
    auto index = indexController()->setIndex();
    auto playerName = scoreController()->userNameAtIndex(index);
    return playerName;
}

QUuid LocalFTPController::currentActivePlayerID()
{
    auto index = indexController()->setIndex();
    auto playerID = scoreController()->userIdAtIndex(index);
    return playerID;
}

QUuid LocalFTPController::tournament()
{
    return _tournament;
}

int LocalFTPController::status()
{
    return _currentStatus;
}

int LocalFTPController::lastPlayerIndex()
{
    auto playerCount = scoreController()->userScoresCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid LocalFTPController::undoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return QUuid();
    _currentStatus = ControllerState::UndoState;
    indexController()->undo();
    auto roundIndex = indexController()->roundIndex();
    auto throwIndex = indexController()->legIndex();
    emit requestSetModelHint(tournament(),
                             currentActivePlayerID(),
                             roundIndex,
                             throwIndex,
                             ModelDisplayHint::HiddenHint);
    auto index = indexController()->setIndex();
    auto playerId = scoreController()->userIdAtIndex(index);
    return playerId;
}

QUuid LocalFTPController::redoTurn()
{
    setCurrentStatus(ControllerState::RedoState);
    auto activeUser = currentActivePlayerID();
    auto roundIndex = indexController()->roundIndex();
    auto throwIndex = indexController()->legIndex();
    indexController()->redo();
    emit requestSetModelHint(tournament(),
                             activeUser,
                             roundIndex,
                             throwIndex,
                             ModelDisplayHint::DisplayHint);
    auto index = indexController()->setIndex();
    auto playerId = scoreController()->userIdAtIndex(index);
    return playerId;
}

void LocalFTPController::addPoint(const int &point, const int &score)
{
    auto tournamentID = tournament();
    auto roundIndex = indexController()->roundIndex();
    auto setIndex = indexController()->setIndex();
    auto throwIndex = indexController()->legIndex();
    QList<int> values = {
        roundIndex,
        setIndex,
        throwIndex,
        point,
        score,
        -1
    };
    auto isWinnerDetermined = status() == ControllerState::WinnerDeclared;
    auto currentPlayer = currentActivePlayerID();
    emit requestAddScore(tournamentID,
                         currentPlayer,
                         values,
                         isWinnerDetermined);
}

void LocalFTPController::handleRequestFromUI()
{
    if(status() == ControllerState::Initialized)
    {
        emit transmitResponse(ControllerResponse::initializedAndReady,{});
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
        auto winnerName = scoreController()->winner();
        emit transmitResponse(ControllerState::WinnerDeclared,{winnerName});
    }
    else if(status() == ControllerState::resetState)
    {
        setCurrentStatus(ControllerState::Initialized);
        emit transmitResponse(ControllerResponse::initializedAndReady,{});
    }
}

void LocalFTPController::nextTurn()
{
    indexController()->next();
    _currentStatus = ControllerState::AwaitsInput;
    sendCurrentTurnValues();
}

void LocalFTPController::declareWinner()
{
    auto index = indexController()->setIndex();
    auto currentPlayerId = scoreController()->userIdAtIndex(index);
    scoreController()->setWinner(currentPlayerId);
    _isActive = false;
    _currentStatus = WinnerDeclared;
}

UserScoreController *LocalFTPController::scoreController() const
{
    return _scoreController;
}

LocalFTPController* LocalFTPController::setScoreController(UserScoreController* scoreController)
{
    _scoreController = scoreController;
    return this;
}


IndexControllerInterface *LocalFTPController::indexController() const
{
    return _indexController;
}

LocalFTPController* LocalFTPController::setIndexController(IndexControllerInterface *indexController)
{
    _indexController = indexController;
    return this;
}

InputValidatorInterface *LocalFTPController::scoreEvaluator() const
{
    return _scoreEvaluator;
}

LocalFTPController* LocalFTPController::setInputValidator(InputValidatorInterface *scoreEvaluator)
{
    _scoreEvaluator = scoreEvaluator;
    return this;
}

void LocalFTPController::setCurrentStatus(int currentStatus)
{
    _currentStatus = currentStatus;
}

LocalFTPController *LocalFTPController::createInstance(const QUuid &tournament)
{
    return new LocalFTPController(tournament);
}

IPointLogisticInterface<QString> *LocalFTPController::pointLogisticInterface() const
{
    return _pointLogisticInterface;
}

LocalFTPController *LocalFTPController::setPointLogisticInterface(IPointLogisticInterface<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void LocalFTPController::handleWakeUpRequest()
{
    setCurrentStatus(ControllerState::Initialized);
    emit transmitResponse(ControllerResponse::initializedAndReady,{});
}

#include "localftpcontroller.h"

void LocalFTPController::start()
{
    if(_currentStatus != ControllerState::Initialized &&
            _currentStatus != ControllerState::Stopped)
    {
        emit transmitResponse(ControllerState::NotInitialized,{});
        return;
    }
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void LocalFTPController::stop()
{
    setCurrentStatus(ControllerState::Stopped);
}

void LocalFTPController::handleAndProcessUserInput(const int &point,
                                              const int &modifierKeyCode)
{
    // Check for status
    if(status() == Stopped ||
            status() == WinnerDeclared)
    {
        emit transmitResponse(ControllerResponse::IsStopped,{});
        return;
    }
    else if(status() == ControllerState::AddScoreState)
    {
        emit transmitResponse(ControllerResponse::IsProcessingUserInput,{});
        return;
    }
    // Calculate score
    auto score = scoreCalculator()->calculateScore(point,modifierKeyCode);
    auto setIndex = indexController()->setIndex();
    auto currentScore = scoreController()->userscoreAtIndex(setIndex);;
    auto newScore = scoreController()->calculateAggregateduserScoreCandidate(setIndex,score);
    // Evaluate input according to point domain and aggregated sum domain
    auto domain = scoreEvaluator()->validateInput(newScore,modifierKeyCode,point);
    switch (domain)
    {
        // In case user enters scores above 180
    case InputValidatorInterface::InputOutOfRange : sendCurrentTurnValues();break;
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
    emit sendCurrentTournamentId(tournament);
}

void LocalFTPController::handleRequestForSingleThrowPlayerScores()
{
    QVariantList list;
    auto count = scoreController()->playersCount();
    for (int i = 0; i < count; ++i) {
        QVariantList subList;
        subList << scoreController()->userNameAtIndex(i)
                << scoreController()->userscoreAtIndex(i);
        list << subList;
    }
    emit transmitResponse(ControllerResponse::ScoresTransmit,list);
}

void LocalFTPController::handleRequestFTPPlayerScores()
{
    auto tournamentId = tournament();
    emit requestFTPScores(tournamentId);
}

void LocalFTPController::handleScoreAddedToDataContext(const QUuid &playerID,
                                                            const int &point,
                                                            const int &score)
{
    scoreController()->setUserScoreAtId(playerID,score);
    auto playerName = scoreController()->userNameFromId(playerID);
    indexController()->syncIndex();
    emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,point,score});
}

void LocalFTPController::handleScoreHintUpdated(const QUuid &playerID,
                                                     const int &point,
                                                     const int &score)
{
    if(status() == ControllerState::UndoState)
    {
        auto newScore = score + point;
        scoreController()->setUserScoreAtId(playerID,newScore);
        auto playerName = scoreController()->userNameFromId(playerID);
        emit transmitResponse(ControllerResponse::ScoreRemove,
                              {playerName,newScore,point});
    }
    else if(status() == ControllerState::RedoState)
    {
        scoreController()->setUserScoreAtId(playerID,score);
        auto playerName = scoreController()->userNameFromId(playerID);
        emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,point,score});
    }
}

void LocalFTPController::handleTournamentResetSuccess()
{
    emit transmitResponse(ControllerResponse::TournamentIsReset,{});
}

void LocalFTPController::handleRequestPersistCurrentState()
{
    emit requestPersistModelState();
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
    _indexController->reset();
    _scoreController->resetScores();
    emit requestResetTournament(tournament());
}

void LocalFTPController::sendCurrentTurnValues()
{
    auto canUndo = indexController()->canUndo();
    auto canRedo = indexController()->canRedo();
    auto roundIndex = indexController()->roundIndex();
    auto currentUserName = currentActiveUser();
    auto setIndex = indexController()->setIndex();
    auto score = scoreController()->userscoreAtIndex(setIndex);;
    auto throwIndex = indexController()->attempt() + 1;
    QString targetRow = "Logistic controller not injected!";
    if(_pointLogisticInterface != nullptr)
        targetRow = pointLogisticInterface()->suggestTargetRow(score,throwIndex);
    QVariantList responseParameters = {
        canUndo,
        canRedo,
        roundIndex,
        currentUserName,
        targetRow
    };
    emit transmitResponse(ControllerResponse::InitializedAndAwaitsInput,
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
    auto playerCount = scoreController()->playersCount();
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
    auto throwIndex = indexController()->attempt();
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
    auto throwIndex = indexController()->attempt();
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
    // Set controller state, unless winner declared
    if(currentStatus() != ControllerState::WinnerDeclared)
        setCurrentStatus(ControllerState::AddScoreState);
    auto tournamentID = tournament();
    auto roundIndex = indexController()->roundIndex();
    auto setIndex = indexController()->setIndex();
    auto throwIndex = indexController()->attempt();
    QVector<int> values = {
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
        emit transmitResponse(ControllerResponse::InitializedAndReady,{});
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
        auto winnerName = scoreController()->winnerUserName();
        emit transmitResponse(ControllerState::WinnerDeclared,{winnerName});
    }
    else if(status() == ControllerState::resetState)
    {
        setCurrentStatus(ControllerState::Initialized);
        emit transmitResponse(ControllerResponse::InitializedAndReady,{});
    }
}

void LocalFTPController::nextTurn()
{
    indexController()->next();
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void LocalFTPController::declareWinner()
{
    auto index = indexController()->setIndex();
    auto currentPlayerId = scoreController()->userIdAtIndex(index);
    scoreController()->setWinner(currentPlayerId);
    setCurrentStatus(ControllerState::WinnerDeclared);
}

int LocalFTPController::currentStatus() const
{
    return _currentStatus;
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

FTPLogisticControllerInterface<QString> *LocalFTPController::pointLogisticInterface() const
{
    return _pointLogisticInterface;
}

LocalFTPController *LocalFTPController::setLogisticInterface(FTPLogisticControllerInterface<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void LocalFTPController::handleWakeUpRequest()
{
    if(scoreController()->winnerId() != QUuid())
        setCurrentStatus(ControllerState::WinnerDeclared);
    else
        setCurrentStatus(ControllerState::Initialized);
    emit transmitResponse(ControllerResponse::InitializedAndReady,{});
}

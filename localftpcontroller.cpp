#include "localftpcontroller.h"

void LocalFtpController::start()
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

void LocalFtpController::stop()
{
    setCurrentStatus(ControllerState::Stopped);
}

void LocalFtpController::handleAndProcessUserInput(const int &point,
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
    auto currentScore = scoreController()->userScore(setIndex);;
    auto newScore = scoreController()->calculateAggregateduserScoreCandidate(setIndex,score);
    // Evaluate input according to point domain and aggregated sum domain
    auto domain = scoreEvaluator()->validateInput(newScore,modifierKeyCode,point);
    switch (domain)
    {
        // In case user enters scores above 180
    case InputValidatorInterface::InputOutOfRange : sendCurrentTurnValues();break;
        case InputValidatorInterface::PointDomain : addPoint(point,score,modifierKeyCode);break;
        case InputValidatorInterface::CriticalDomain : addPoint(point,score,modifierKeyCode);break;
        case InputValidatorInterface::TargetDomain : {
            declareWinner();
            addPoint(point,score,modifierKeyCode);
            break;
        }
        case InputValidatorInterface::OutsideDomain : addPoint(0,currentScore,modifierKeyCode);break;
    }
}

void LocalFtpController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = this->tournament();
    emit sendCurrentTournamentId(tournament);
}

void LocalFtpController::handleRequestForSingleThrowPlayerScores()
{
    QVariantList list;
    auto count = scoreController()->playersCount();
    for (int i = 0; i < count; ++i) {
        QVariantList subList;
        subList << scoreController()->userNameAtIndex(i)
                << scoreController()->userScore(i);
        list << subList;
    }
    emit transmitResponse(ControllerResponse::ScoresTransmit,list);
}

void LocalFtpController::handleRequestFtpPlayerScores()
{
    auto tournamentId = tournament();
    emit requestFTPScores(tournamentId);
}

void LocalFtpController::handleScoreAddedToDataContext(const QUuid &playerId,
                                                            const int &point,
                                                            const int &score)
{
    scoreController()->subtractPlayerScore(playerId,score);
    auto playerName = scoreController()->userNameFromId(playerId);
    auto currentScore = scoreController()->userScore(playerId);
    indexController()->syncIndex();
    emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,point,currentScore});
}

void LocalFtpController::handleScoreHintUpdated(const QUuid &playerId,
                                                const int &point,
                                                const int &score)
{
    if(this->status() == ControllerState::UndoState)
    {
        scoreController()->addPlayerScore(playerId,score);
        auto newScore = scoreController()->userScore(playerId);
        auto playerName = scoreController()->userNameFromId(playerId);
        emit transmitResponse(ControllerResponse::ScoreRemove,
                              {playerName,newScore,point});
    }
    else if(this->status() == ControllerState::RedoState)
    {
        scoreController()->subtractPlayerScore(playerId,score);
        auto newScore = scoreController()->userScore(playerId);
        auto playerName = scoreController()->userNameFromId(playerId);
        emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,point,newScore});
    }
}

void LocalFtpController::handleTournamentResetSuccess()
{
    emit transmitResponse(ControllerResponse::TournamentIsReset,{});
}

void LocalFtpController::handleRequestPersistCurrentState()
{
    emit requestPersistModelState();
}

ScoreCalculatorInterface *LocalFtpController::scoreCalculator() const
{
    return _scoreCalculatorService;
}

LocalFtpController *LocalFtpController::setScoreCalculator(ScoreCalculatorInterface *service)
{
    _scoreCalculatorService = service;
    return this;
}

void LocalFtpController::handleResetTournament()
{
    _currentStatus = ControllerState::resetState;
    _indexController->reset();
    _scoreController->resetScores();
    emit requestResetTournament(tournament());
}

void LocalFtpController::sendCurrentTurnValues()
{
    auto canUndo = indexController()->canUndo();
    auto canRedo = indexController()->canRedo();
    auto roundIndex = indexController()->roundIndex();
    auto currentUserName = currentActiveUser();
    auto setIndex = indexController()->setIndex();
    auto score = scoreController()->userScore(setIndex);;
    auto attemptIndex = indexController()->attempt() + 1;
    QString targetRow = "Logistic controller not injected!";
    if(_pointLogisticInterface != nullptr)
        targetRow = pointLogisticInterface()->suggestTargetRow(score,attemptIndex);
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

QString LocalFtpController::currentActiveUser()
{
    auto index = indexController()->setIndex();
    auto playerName = scoreController()->userNameAtIndex(index);
    return playerName;
}

QUuid LocalFtpController::currentActivePlayerID()
{
    auto index = indexController()->setIndex();
    auto playerID = scoreController()->userIdAtIndex(index);
    return playerID;
}

QUuid LocalFtpController::tournament()
{
    return _tournament;
}

int LocalFtpController::status()
{
    return _currentStatus;
}

int LocalFtpController::lastPlayerIndex()
{
    auto playerCount = scoreController()->playersCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid LocalFtpController::undoTurn()
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
    auto playerId = currentActivePlayerID();
    return playerId;
}

QUuid LocalFtpController::redoTurn()
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

void LocalFtpController::addPoint(const int& point,
                                  const int& score,
                                  const int& keyCode)
{
    // Set controller state, unless winner declared
    if(currentStatus() != ControllerState::WinnerDeclared)
        setCurrentStatus(ControllerState::AddScoreState);
    auto tournamentID = tournament();
    auto roundIndex = indexController()->roundIndex();
    auto setIndex = indexController()->setIndex();
    auto attemptIndex = indexController()->attempt();
    auto isWinnerDetermined = status() == ControllerState::WinnerDeclared;
    auto currentPlayer = currentActivePlayerID();
    emit requestAddFtpScore (tournamentID,
                         currentPlayer,
                         roundIndex,
                         setIndex,
                         attemptIndex,
                         point,
                         score,
                         keyCode,
                         isWinnerDetermined);
}

void LocalFtpController::handleRequestFromUI()
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

void LocalFtpController::nextTurn()
{
    indexController()->next();
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void LocalFtpController::declareWinner()
{
    auto index = indexController()->setIndex();
    auto currentPlayerId = scoreController()->userIdAtIndex(index);
    scoreController()->setWinner(currentPlayerId);
    setCurrentStatus(ControllerState::WinnerDeclared);
}

int LocalFtpController::currentStatus() const
{
    return _currentStatus;
}

void LocalFtpController::recieveFtpIndexesAndEntities(const int& totalTurns,
                                                      const int& turns,
                                                      const int& roundIndex,
                                                      const int& setIndex,
                                                      const int& attemptIndex,
                                                      const QVector<AbstractFtpController::Player> &players,
                                                      const QVector<AbstractFtpController::PlayerScore> &playerScores)
{
    indexController()->setIndexes(totalTurns,turns,
                                  roundIndex,setIndex,
                                  attemptIndex);
    indexController()->setPlayersCount(players.count());
    for (auto i = players.constBegin(); i != players.constEnd(); ++i) {
        auto p = *i;
        scoreController()->addPlayerEntity(p.first,p.second);
    }

    for (auto i = playerScores.constBegin(); i != playerScores.constEnd(); ++i)
    {
        auto p = *i;
        scoreController()->subtractPlayerScore(p.first,p.second);
    }
    if(scoreController()->winnerId() != QUuid())
        setCurrentStatus(ControllerState::WinnerDeclared);
    else
        setCurrentStatus(ControllerState::Initialized);
    emit transmitResponse(ControllerResponse::InitializedAndReady,{});
}

ScoreController *LocalFtpController::scoreController() const
{
    return _scoreController;
}

LocalFtpController* LocalFtpController::setScoreController(ScoreController* scoreController)
{
    _scoreController = scoreController;
    return this;
}


IndexControllerInterface *LocalFtpController::indexController() const
{
    return _indexController;
}

LocalFtpController* LocalFtpController::setIndexController(IndexControllerInterface *indexController)
{
    _indexController = indexController;
    return this;
}

InputValidatorInterface *LocalFtpController::scoreEvaluator() const
{
    return _scoreEvaluator;
}

LocalFtpController* LocalFtpController::setInputValidator(InputValidatorInterface *scoreEvaluator)
{
    _scoreEvaluator = scoreEvaluator;
    return this;
}

void LocalFtpController::setCurrentStatus(int currentStatus)
{
    _currentStatus = currentStatus;
}

LocalFtpController *LocalFtpController::createInstance(const QUuid &tournament)
{
    return new LocalFtpController(tournament);
}

FTPLogisticControllerInterface<QString> *LocalFtpController::pointLogisticInterface() const
{
    return _pointLogisticInterface;
}

LocalFtpController *LocalFtpController::setLogisticInterface(FTPLogisticControllerInterface<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void LocalFtpController::initialize()
{
    /*
    if(scoreController()->winnerId() != QUuid())
        setCurrentStatus(ControllerState::WinnerDeclared);
    else
        setCurrentStatus(ControllerState::Initialized);
    emit transmitResponse(ControllerResponse::InitializedAndReady,{});
     */
    emit requestFtpIndexesAndScores(tournament());
}

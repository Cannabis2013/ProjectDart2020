#include "localftpcontroller.h"

void LocalFTPController::start()
{
    if(_currentStatus != ControllerState::Initialized &&
            _currentStatus != ControllerState::Stopped)
    {
        transmitResponse(ControllerState::NotInitialized,{});
        return;
    }
    _isActive = true;
    _currentStatus = ControllerState::AwaitsInput;
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
    auto currentScore = playerScore(currentSetIndex());
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
    emit requestTournamentMetaData(currentTournamentID());
}

void LocalFTPController::handleRequestForPlayerScores()
{
    PlayerPairs assignedPlayerPairs;
    for (int i = 0; i < _assignedPlayerTupples.count(); ++i) {
        auto assignedPlayerTupple = _assignedPlayerTupples.at(i);
        auto assignedPlayerID = assignedPlayerTupple.first;
        auto assignedPlayerName = assignedPlayerTupple.second;
        auto assignedPlayerPair = PlayerPair(assignedPlayerID,assignedPlayerName);
        assignedPlayerPairs << assignedPlayerPair;
    }
    emit sendAssignedTournamentPlayers(currentTournamentID(),assignedPlayerPairs);
}

void LocalFTPController::recieveTournamentDetails(const QUuid &tournament,
                                                const QString &winner,
                                                const PlayerPairs &assignedPlayerPairs)
{
    _currentTournament = tournament;
    _winner = winner;
    _assignedPlayerTupples = setPlayerTubblesFromPairs(assignedPlayerPairs,keyPoint());
    emit requestTournamentIndexes(_currentTournament);
}

void LocalFTPController::recieveTournamentIndexes(const int &roundIndex,
                                                const int &setIndex,
                                                const int &throwIndex,
                                                const int &turnIndex,
                                                const int &totalTurns,
                                                const QList<int> &playerScores)
{
    _roundIndex = roundIndex;
    _setIndex = setIndex;
    _throwIndex = throwIndex;
    _turnIndex = turnIndex;
    _totalTurns = totalTurns;
    updatePlayerTubbles(playerScores);

    if(determinedWinnerName() != "")
        _currentStatus = ControllerState::WinnerDeclared;
    else
        _currentStatus = ControllerState::Initialized;

    emit transmitResponse(ControllerResponse::controllerInitializedAndReady,{});
}

void LocalFTPController::handleScoreAddedToDataContext(const QUuid &playerID,
                                                            const int &point,
                                                            const int &score)
{
    setPlayerScore(playerID,score);
    auto playerName = getPlayerNameFromID(playerID);
    _totalTurns = _turnIndex;
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
        setPlayerScore(playerID,newScore);
        auto playerName = getPlayerNameFromID(playerID);
        emit transmitResponse(ControllerResponse::ScoreRemove,
                              {playerName,newScore,point});
    }
    else if(status() == ControllerState::RedoState)
    {
        setPlayerScore(playerID,score);
        auto playerName = getPlayerNameFromID(playerID);
        emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,point,score});
    }
}

void LocalFTPController::handleTournamentResetSuccess()
{
    // Reset controller index values
    _turnIndex = 0;
    _totalTurns = 0;
    _roundIndex = 1;
    _setIndex = 0;
    _throwIndex = 0;
    _winner = QString();
    // Reset playerscores to target point
    QStringList playerNamesList;
    for (int i = 0; i < playerCount(); ++i){
        setPlayerScore(i,keyPoint());
        auto playerName = playerNameFromIndex(i);
        playerNamesList << playerName;
    }
    emit transmitResponse(ControllerResponse::transmitInitialScore,{keyPoint(),playerNamesList});

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
    emit requestResetTournament(currentTournamentID());
}

void LocalFTPController::sendCurrentTurnValues()
{
    auto canUndo = canUndoTurn();
    auto canRedo = canRedoTurn();
    auto currentRound = currentRoundIndex();
    auto currentUserName = currentActiveUser();
    auto score = playerScore(currentSetIndex());
    auto throwSuggestion = pointLogisticInterface()->throwSuggestion(score,currentThrowIndex() + 1);
    emit transmitResponse(ControllerResponse::controllerInitializedAndAwaitsInput,
                          {canUndo,canRedo,currentRound,currentUserName,throwSuggestion});
}

QString LocalFTPController::currentActiveUser()
{
    auto index = currentSetIndex();
    auto tupple = _assignedPlayerTupples.at(index);
    auto playerName = tupple.second;
    return playerName;
}

QUuid LocalFTPController::currentActivePlayerID()
{
    auto index = currentSetIndex();
    auto tupple = _assignedPlayerTupples.at(index);
    auto playerID = tupple.first;
    return playerID;
}

int LocalFTPController::currentRoundIndex()
{
    return indexController()->roundIndex();
}

int LocalFTPController::currentPlayerIndex()
{
    return indexController()->roundIndex();
}

int LocalFTPController::currentSetIndex()
{
    return indexController()->setIndex();
}

int LocalFTPController::currentThrowIndex()
{
    return indexController()->legIndex();
}

int LocalFTPController::lastPlayerIndex()
{
    return _assignedPlayerTupples.count() - 1;
}

int LocalFTPController::playerIndex()
{
    return _setIndex;
}

QUuid LocalFTPController::undoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return QUuid();
    _currentStatus = ControllerState::UndoState;
    indexController()->undo();
    emit requestSetModelHint(currentTournamentID(),
                             currentActivePlayerID(),
                             currentRoundIndex(),
                             currentThrowIndex(),
                             ModelDisplayHint::HiddenHint);
    auto index = currentSetIndex();
    return _assignedPlayerTupples.at(index).first;
}

QUuid LocalFTPController::redoTurn()
{
    setCurrentStatus(ControllerState::RedoState);
    auto activeUser = currentActivePlayerID();
    auto roundIndex = currentRoundIndex();
    auto throwIndex = currentThrowIndex();
    indexController()->redo();
    emit requestSetModelHint(currentTournamentID(),
                             activeUser,
                             roundIndex,
                             throwIndex,
                             ModelDisplayHint::DisplayHint);
    auto index = currentSetIndex();
    return _assignedPlayerTupples.at(index).first;
}


bool LocalFTPController::canUndoTurn()
{
    auto result = indexController()->canUndo();
    return result;
}

bool LocalFTPController::canRedoTurn()
{
    auto result = indexController()->canRedo();
    return result;
}

void LocalFTPController::addPoint(const int &point, const int &score)
{
    auto tournamentID = currentTournamentID();
    QList<int> values;
    values.append(currentRoundIndex());
    values.append(currentPlayerIndex());
    values.append(currentThrowIndex());
    values.append(point);
    values.append(score);
    values.append(-1);
    auto isWinnerDetermined = status() == ControllerState::WinnerDeclared;
    auto currentPlayer = currentActivePlayerID();
    emit requestAddScore(tournamentID,
                         currentPlayer,
                         values,
                         isWinnerDetermined);
}

int LocalFTPController::currentTurnIndex()
{
    return _turnIndex;
}

bool LocalFTPController::isIndexOffset()
{
    return _isOff;
}

void LocalFTPController::handleRequestFromUI()
{
    if(status() == ControllerState::Initialized)
    {
        emit transmitResponse(ControllerResponse::controllerInitializedAndReady,{});
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
        auto winnerName = determinedWinnerName();
        emit transmitResponse(ControllerState::WinnerDeclared,{winnerName});
    }
    else if(status() == ControllerState::resetState)
    {
        setCurrentStatus(ControllerState::Initialized);
        emit transmitResponse(ControllerResponse::controllerInitializedAndReady,{});
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
    _winner = currentActiveUser();
    _isActive = false;
    _currentStatus = WinnerDeclared;
}

void LocalFTPController::incrementTurnIndex()
{
    if(_turnIndex == _totalTurns)
        _totalTurns++;
    _turnIndex++;
}

void LocalFTPController::incrementRoundIndex()
{
    _roundIndex++;
}

void LocalFTPController::incrementSetIndex()
{
    _setIndex++;
}

void LocalFTPController::resetSetIndex()
{
    _setIndex = 0;
}

void LocalFTPController::incrementThrowIndex()
{
    _throwIndex++;
}

void LocalFTPController::resetThrowIndex()
{
    _throwIndex = 0;
}

bool LocalFTPController::checkForEndOfSet()
{
    auto result = currentTurnIndex() % numberOfThrows() == 0;
    return result;
}

int LocalFTPController::playerScore(const int &index)
{
    auto tubble = _assignedPlayerTupples.at(index);
    auto score = tubble.third;;
    return score;
}

void LocalFTPController::setPlayerScore(const int &index, const int &newScore)
{
    auto tubble = _assignedPlayerTupples.at(index);
    tubble.third = newScore;
    _assignedPlayerTupples.replace(index,tubble);
}

void LocalFTPController::setPlayerScore(const QUuid &playerID, const int &newScore)
{
    for (int i = 0; i < _assignedPlayerTupples.count(); ++i) {
        auto pair = _assignedPlayerTupples.at(i);
        auto id = pair.first;
        if(id == playerID)
        {
            setPlayerScore(i, newScore);
            return;
        }
    }
}

QString LocalFTPController::getPlayerNameFromID(const QUuid &playerID)
{
    for (auto tupple : _assignedPlayerTupples) {
        auto id = tupple.first;
        if(id == playerID)
        {
            auto playerName = tupple.second;
            return playerName;
        }
    }
    return QString();
}

QString LocalFTPController::playerNameFromIndex(const int &index)
{
    auto tupple = _assignedPlayerTupples.at(index);
    auto playerName = tupple.second;
    return playerName;
}

PlayerTubbles LocalFTPController::setPlayerTubblesFromPairs(PlayerPairs pairs, const int &initialThirdValue)
{
    PlayerTubbles tubbles;
    for (int i = 0; i < pairs.count(); ++i) {
        auto playerPair = pairs.at(i);
        auto playerID = playerPair.first;
        auto playerName = playerPair.second;
        auto tubble = PlayerTupple(playerID,playerName,initialThirdValue);
        tubbles << tubble;
    }
    return tubbles;
}

void LocalFTPController::updatePlayerTubbles(const QList<int> &scores)
{
    if(scores.count() != _assignedPlayerTupples.count())
        throw "Inconsistency detected";

    for (int i = 0; i < scores.count(); ++i) {
        auto score = scores.at(i);
        auto tubble = _assignedPlayerTupples.at(i);
        tubble.third = score;
        _assignedPlayerTupples.replace(i,tubble);
    }
}

int LocalFTPController::keyPoint() const
{
    return _keyPoint;
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

LocalFTPController::LocalFTPController(const int &keyPoint, const int &numberOfThrows)
{
    _keyPoint = keyPoint;
    _numberOfThrows = numberOfThrows;
}

int LocalFTPController::numberOfThrows() const
{
    return _numberOfThrows;
}

LocalFTPController* LocalFTPController::setNumberOfThrows(int numberOfThrows)
{
    _numberOfThrows = numberOfThrows;
    return this;
}

void LocalFTPController::setCurrentStatus(int currentStatus)
{
    _currentStatus = currentStatus;
}

LocalFTPController *LocalFTPController::createInstance(const int &keyPoint,
                                                       const int &numberOfThrows)
{
    return new LocalFTPController(keyPoint,numberOfThrows);
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

void LocalFTPController::consistencyCheck()
{
    Q_UNIMPLEMENTED();
}

QString LocalFTPController::determinedWinnerName()
{
    return _winner;
}

#include "pointftpcontroller.h"

void PointFTPController::start()
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

void PointFTPController::stop()
{
    _isActive = false;
    _currentStatus = ControllerState::Stopped;
    emit transmitResponse(ControllerResponse::isStopped,{});
}

void PointFTPController::handleAndProcessUserInput(const int &point,
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
    // Initialize pointmultiplier
    auto pointMultiplier = modifierKeyCode == KeyMappings::TrippleModifier ? 3 :
                            modifierKeyCode == KeyMappings::DoubleModifier ? 2 :
                            modifierKeyCode == KeyMappings::SingleModifer ? 1 : 0;
    // Calculate point
    auto score = point*pointMultiplier;

    auto currentScore = playerScore(_setIndex);
    auto newScore = currentScore - score;

    // Evaluate input according to point domain and aggregated sum domain
    switch (validateInput(newScore,modifierKeyCode,point))
    {
        case PointDomains::InvalidDomain : throw INVALID_DOMAIN;
        case PointDomains::PointDomain : addPoint(score,newScore);break;
        case PointDomains::CriticalDomain : addPoint(score,newScore);break;
        case PointDomains::TargetDomain : {
            declareWinner();
            addPoint(score,newScore);
            break;
        }
    case PointDomains::OutsideDomain : addPoint(0,currentScore);break;
    }
}

void PointFTPController::handleRequestForCurrentTournamentMetaData()
{
    emit requestTournamentMetaData(currentTournamentID());
}

void PointFTPController::handleRequestForPlayerScores()
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

void PointFTPController::recieveTournamentDetails(const QUuid &tournament,
                                                const QString &winner,
                                                const int &keyPoint,
                                                const int &terminalKeyCode,
                                                const int &numberOfThrows,
                                                const PlayerPairs &assignedPlayerPairs)
{
    _currentTournament = tournament;
    _keyPoint = keyPoint;
    _numberOfThrows = numberOfThrows;
    _assignedPlayerTupples = setPlayerTubblesFromPairs(assignedPlayerPairs,keyPoint);
    pointLogisticInterface()->setLastThrowKeyCode(terminalKeyCode);
    _winner = winner;
    emit requestTournamentIndexes(_currentTournament);
}

void PointFTPController::recieveTournamentIndexes(const int &roundIndex,
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

void PointFTPController::handleScoreAddedToDataContext(const QUuid &playerID,
                                                            const int &point,
                                                            const int &score)
{
    setPlayerScore(playerID,score);
    auto playerName = getPlayerNameFromID(playerID);
    _totalTurns = _turnIndex;
    emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,point,score});
}

void PointFTPController::handleDataContextUpdated()
{
    _currentStatus = ControllerState::AwaitsInput;
    sendCurrentTurnValues();
}

void PointFTPController::handleScoreHintUpdated(const QUuid &playerID,
                                                     const int &point,
                                                     const int &score)
{
    if(status() == ControllerState::UndoState)
    {
        auto newScore = score + point;
        setPlayerScore(playerID,newScore);
        auto playerName = getPlayerNameFromID(playerID);
        emit transmitResponse(ControllerResponse::ScoreRemove,{playerName});
    }
    else if(status() == ControllerState::RedoState)
    {
        setPlayerScore(playerID,score);
        auto playerName = getPlayerNameFromID(playerID);
        emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,point,score});
    }
}

void PointFTPController::handleTournamentResetSuccess()
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

void PointFTPController::handleResetTournament()
{
    _currentStatus = ControllerState::resetState;
    emit requestResetTournament(currentTournamentID());
}

void PointFTPController::sendCurrentTurnValues()
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

QString PointFTPController::currentActiveUser()
{
    auto tupple = _assignedPlayerTupples.at(currentSetIndex());
    auto playerName = tupple.second;
    return playerName;
}

QUuid PointFTPController::currentActivePlayerID()
{
    auto tupple = _assignedPlayerTupples.at(currentSetIndex());
    auto playerID = tupple.first;
    return playerID;
}

int PointFTPController::currentThrowIndex()
{
    return _throwIndex;
}

int PointFTPController::lastPlayerIndex()
{
    return _assignedPlayerTupples.count() - 1;
}

int PointFTPController::playerIndex()
{
    return _setIndex;
}

QUuid PointFTPController::undoTurn()
{
    if(_turnIndex <= 0)
        return QUuid();
    else if(status() == ControllerState::WinnerDeclared)
        return QUuid();

    _currentStatus = ControllerState::UndoState;

    _turnIndex--;
    if(_throwIndex > 0)
    {
        _throwIndex--;
        emit requestSetModelHint(currentTournamentID(),
                                 currentActivePlayerID(),
                                 currentRoundIndex(),
                                 currentThrowIndex(),
                                 ModelDisplayHint::HiddenHint);
        return _assignedPlayerTupples.at(_setIndex).first;
    }

    _throwIndex = 2;

    if(_setIndex == 0)
    {
        _setIndex = lastPlayerIndex();
        _roundIndex--;
    }
    else
    {
        _setIndex--;
    }
    emit requestSetModelHint(currentTournamentID(),
                             currentActivePlayerID(),
                             currentRoundIndex(),
                             currentThrowIndex(),
                             ModelDisplayHint::HiddenHint);
    return _assignedPlayerTupples.at(_setIndex).first;
}

QUuid PointFTPController::redoTurn()
{
    if(_turnIndex >= _totalTurns)
        return QUuid();
    else if(status() == ControllerState::WinnerDeclared)
        return QUuid();

    auto currentActiveUser = this->currentActivePlayerID();
    auto currentRoundIndex = this->currentRoundIndex();
    auto currentThrowIndex = this->currentThrowIndex();

    _currentStatus = ControllerState::RedoState;

    if(++_throwIndex >= _numberOfThrows)
    {
        _throwIndex = 0;
        if(_setIndex == lastPlayerIndex())
        {
            _setIndex = 0;
            _roundIndex++;
        }
        else
            _setIndex++;
    }
    _turnIndex++;
    emit requestSetModelHint(currentTournamentID(),
                             currentActiveUser,
                             currentRoundIndex,
                             currentThrowIndex,
                             ModelDisplayHint::DisplayHint);
    return _assignedPlayerTupples.at(_setIndex).first;
}


bool PointFTPController::canUndoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return false;
    return _turnIndex > 0;
}

bool PointFTPController::canRedoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return false;
    return _turnIndex < _totalTurns;
}

int PointFTPController::validateCurrentState(const int &currentScore)
{
    auto playerSum = _keyPoint - currentScore;

    if(playerSum > criticalLimit)
        return PointDomain;
    else if(playerSum <= criticalLimit && playerSum > 0)
        return CriticalDomain;
    else if(playerSum == 0)
        return TargetDomain;
    else
        return OutsideDomain;
}

int PointFTPController::validateInput(const int &currentScore,
                                    const int &modifierKeyCode,
                                    const int &userInput)
{
    int minimumAllowedScore = 2;
    if(terminateConditionModifier() == KeyMappings::SingleModifer)
        minimumAllowedScore = 1;
    else if(terminateConditionModifier() == KeyMappings::DoubleModifier)
        minimumAllowedScore = 2;
    else
        minimumAllowedScore = 3;


    if(currentScore > criticalLimit)
        return PointDomain;
    else if(currentScore <= criticalLimit && currentScore >= minimumAllowedScore)
        return CriticalDomain;
    else if(currentScore == 0 && (modifierKeyCode == terminateConditionModifier() || userInput == bullsEye))
        return TargetDomain;
    else
        return OutsideDomain;
}

void PointFTPController::addPoint(const int &point, const int &score)
{
    auto tournamentID = currentTournamentID();
    auto roundIndex = currentRoundIndex();
    auto setIndex = currentPlayerIndex();
    auto throwIndex = currentThrowIndex();
    auto isWinnerDetermined = status() == ControllerState::WinnerDeclared;
    auto currentPlayer = currentActivePlayerID();
    emit requestAddScore(tournamentID,
                   currentPlayer,
                   roundIndex,
                   setIndex,
                   throwIndex,
                   point,
                   score,
                   -1,
                   isWinnerDetermined);
}

int PointFTPController::currentTurnIndex()
{
    return _turnIndex;
}

bool PointFTPController::isIndexOffset()
{
    return _isOff;
}

void PointFTPController::handleRequestFromUI()
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

void PointFTPController::nextTurn()
{
    incrementTurnIndexes();

    if(_turnIndex % _numberOfThrows == 0)
    {
        _setIndex++;
        _throwIndex = 0;
        if(_setIndex >= _assignedPlayerTupples.count()){
            _roundIndex++;
            _setIndex = 0;
        }
        _currentStatus = ControllerState::UpdateContextState;
    }
    else
    {
        _throwIndex++;
        _currentStatus = ControllerState::AwaitsInput;
    }
    sendCurrentTurnValues();
}

void PointFTPController::declareWinner()
{
    _winner = currentActiveUser();
    _isActive = false;
    _currentStatus = WinnerDeclared;
}

void PointFTPController::incrementTurnIndexes()
{
    if(_turnIndex == _totalTurns)
        _totalTurns++;
    _turnIndex++;
}

int PointFTPController::playerScore(const int &index)
{
    auto tubble = _assignedPlayerTupples.at(index);
    auto score = tubble.third;;
    return score;
}

void PointFTPController::setPlayerScore(const int &index, const int &newScore)
{
    auto tubble = _assignedPlayerTupples.at(index);
    tubble.third = newScore;
    _assignedPlayerTupples.replace(index,tubble);
}

void PointFTPController::setPlayerScore(const QUuid &playerID, const int &newScore)
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

QString PointFTPController::getPlayerNameFromID(const QUuid &playerID)
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

QString PointFTPController::playerNameFromIndex(const int &index)
{
    auto tupple = _assignedPlayerTupples.at(index);
    auto playerName = tupple.second;
    return playerName;
}

PlayerTubbles PointFTPController::setPlayerTubblesFromPairs(PlayerPairs pairs, const int &initialThirdValue)
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

void PointFTPController::updatePlayerTubbles(const QList<int> &scores)
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

int PointFTPController::keyPoint() const
{
    return _keyPoint;
}

void PointFTPController::setCurrentStatus(int currentStatus)
{
    _currentStatus = currentStatus;
}

int PointFTPController::terminateConditionModifier() const
{
    return pointLogisticInterface()->lastThrowKeyCode();
}

IPointLogisticInterface<QString> *PointFTPController::pointLogisticInterface() const
{
    return _pointLogisticInterface;
}

AbstractGameController *PointFTPController::setPointLogisticInterface(IPointLogisticInterface<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void PointFTPController::consistencyCheck()
{
    Q_UNIMPLEMENTED();
}

QString PointFTPController::determinedWinnerName()
{
    return _winner;
}

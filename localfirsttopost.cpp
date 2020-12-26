#include "localfirsttopost.h"

void LocalFirstToPost::start()
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

void LocalFirstToPost::stop()
{
    _isActive = false;
    _currentStatus = ControllerState::Stopped;
    emit transmitResponse(ControllerResponse::isStopped,{});
}

void LocalFirstToPost::handleAndProcessUserInput(const int &userInput,
                                                 const int &modifierKeyCode)
{
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

    _currentStatus = ControllerState::AddScoreState;

    auto pointMultiplier = modifierKeyCode == KeyMappings::TrippleModifier ? 3 :
                            modifierKeyCode == KeyMappings::DoubleModifier ? 2 :
                            modifierKeyCode == KeyMappings::SingleModifer ? 1 : 0;

    auto calculatedPoint = userInput*pointMultiplier;

    auto currentScore = playerScore(_setIndex);
    auto newScore = currentScore - calculatedPoint;

    // Evaluate input according to point domain and aggregated sum domain
    switch (validateInput(newScore,modifierKeyCode,userInput))
    {
        case PointDomains::InvalidDomain : throw INVALID_DOMAIN;
        case PointDomains::PointDomain : addPoint(calculatedPoint,newScore);break;
        case PointDomains::CriticalDomain : addPoint(calculatedPoint,newScore);break;
        case PointDomains::TargetDomain : {
            declareWinner();
            addPoint(calculatedPoint,newScore);
            break;
        }
    case PointDomains::OutsideDomain : addPoint(0,currentScore);break;
    }
}

void LocalFirstToPost::handleRequestForCurrentTournamentMetaData()
{
    emit requestTournamentMetaData(currentTournamentID());
}

void LocalFirstToPost::handleRequestForPlayerScores()
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

void LocalFirstToPost::recieveTournamentDetails(const QUuid &tournament,
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

void LocalFirstToPost::recieveTournamentIndexes(const int &roundIndex,
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

void LocalFirstToPost::handleScoreAddedToDataContext(const QUuid &playerID,
                                                            const int &point,
                                                            const int &score)
{
    setPlayerScore(playerID,score);
    auto playerName = getPlayerNameFromID(playerID);
    _totalTurns = _turnIndex;
    emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,point,score});
}

void LocalFirstToPost::handleDataContextUpdated()
{
    _currentStatus = ControllerState::AwaitsInput;
    sendCurrentTurnValues();
}

void LocalFirstToPost::handleScoreHintUpdated(const QUuid &playerID,
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

void LocalFirstToPost::handleTournamentResetSuccess()
{
    // Reset controller index values
    _turnIndex = 0;
    _totalTurns = 0;
    _roundIndex = 1;
    _setIndex = 0;
    _throwIndex = 0;
    _winner = QString();
    // Reset playerscores to target point
    for (int i = 0; i < playerCount(); ++i)
        setPlayerScore(i,keyPoint());
    _currentStatus = ControllerState::Initialized;
    emit requestTournamentIndexes(currentTournamentID());
    emit transmitResponse(ControllerResponse::controllerReset,{});
}

void LocalFirstToPost::handleResetTournament()
{
    _currentStatus = ControllerState::resetState;
    emit requestResetTournament(currentTournamentID());
}

void LocalFirstToPost::sendCurrentTurnValues()
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

QString LocalFirstToPost::currentActiveUser()
{
    auto tupple = _assignedPlayerTupples.at(currentSetIndex());
    auto playerName = tupple.second;
    return playerName;
}

QUuid LocalFirstToPost::currentActivePlayerID()
{
    auto tupple = _assignedPlayerTupples.at(currentSetIndex());
    auto playerID = tupple.first;
    return playerID;
}

int LocalFirstToPost::currentThrowIndex()
{
    return _throwIndex;
}

int LocalFirstToPost::lastPlayerIndex()
{
    return _assignedPlayerTupples.count() - 1;
}

int LocalFirstToPost::playerIndex()
{
    return _setIndex;
}

QUuid LocalFirstToPost::undoTurn()
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

QUuid LocalFirstToPost::redoTurn()
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


bool LocalFirstToPost::canUndoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return false;
    return _turnIndex > 0;
}

bool LocalFirstToPost::canRedoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return false;
    return _turnIndex < _totalTurns;
}

int LocalFirstToPost::validateCurrentState(const int &currentScore)
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

int LocalFirstToPost::validateInput(const int &currentScore,
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

void LocalFirstToPost::addPoint(const int &point, const int &score)
{
    auto tournamentID = currentTournamentID();
    auto roundIndex = currentRoundIndex();
    auto setIndex = currentPlayerIndex();
    auto throwIndex = currentThrowIndex();
    auto isWinnerDetermined = status() == ControllerState::WinnerDeclared;
    auto currentPlayer = currentActivePlayerID();
    emit sendScore(tournamentID,
                   currentPlayer,
                   roundIndex,
                   setIndex,
                   throwIndex,
                   point,
                   score,
                   -1,
                   isWinnerDetermined);
}

int LocalFirstToPost::currentTurnIndex()
{
    return _turnIndex;
}

bool LocalFirstToPost::isIndexOffset()
{
    return _isOff;
}

void LocalFirstToPost::handleRequestFromUI()
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
        _currentStatus = ControllerState::AwaitsInput;
        sendCurrentTurnValues();
    }
    else if(status() == ControllerState::RedoState)
    {
        _currentStatus = ControllerState::AwaitsInput;
        sendCurrentTurnValues();
    }
    else if(status() == ControllerState::WinnerDeclared)
    {
        auto winnerName = determinedWinnerName();
        emit transmitResponse(ControllerState::WinnerDeclared,{winnerName});
    }
}

void LocalFirstToPost::nextTurn()
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

void LocalFirstToPost::declareWinner()
{
    _winner = currentActiveUser();
    _isActive = false;
    _currentStatus = WinnerDeclared;
}

void LocalFirstToPost::incrementTurnIndexes()
{
    if(_turnIndex == _totalTurns)
        _totalTurns++;
    _turnIndex++;
}

int LocalFirstToPost::playerScore(const int &index)
{
    auto tubble = _assignedPlayerTupples.at(index);
    auto score = tubble.third;;
    return score;
}

void LocalFirstToPost::setPlayerScore(const int &index, const int &newScore)
{
    auto tubble = _assignedPlayerTupples.at(index);
    tubble.third = newScore;
    _assignedPlayerTupples.replace(index,tubble);
}

void LocalFirstToPost::setPlayerScore(const QUuid &playerID, const int &newScore)
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

QString LocalFirstToPost::getPlayerNameFromID(const QUuid &playerID)
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

PlayerTubbles LocalFirstToPost::setPlayerTubblesFromPairs(PlayerPairs pairs, const int &initialThirdValue)
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

void LocalFirstToPost::updatePlayerTubbles(const QList<int> &scores)
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

int LocalFirstToPost::keyPoint() const
{
    return _keyPoint;
}

int LocalFirstToPost::terminateConditionModifier() const
{
    return pointLogisticInterface()->lastThrowKeyCode();
}

IPointLogisticInterface<QString> *LocalFirstToPost::pointLogisticInterface() const
{
    return _pointLogisticInterface;
}

AbstractGameController *LocalFirstToPost::setPointLogisticInterface(IPointLogisticInterface<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void LocalFirstToPost::consistencyCheck()
{
    Q_UNIMPLEMENTED();
}

QString LocalFirstToPost::determinedWinnerName()
{
    return _winner;
}

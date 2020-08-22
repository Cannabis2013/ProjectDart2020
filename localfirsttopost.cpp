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
    emit transmitResponse(_currentStatus,{});
}

void LocalFirstToPost::handleAndProcessUserInput(const int &point, const int &modifierKeyCode)
{
    if(status() == Idle ||
            status() == Stopped ||
            status() == WinnerDeclared)
    {
        emit transmitResponse(status(),{});
        return;
    }

    _currentStatus = ControllerState::AddScoreState;

    auto pointMultiplier = modifierKeyCode == KeyMappings::TrippleModifier ? 3 :
                            modifierKeyCode == KeyMappings::DoubleModifier ? 2 :
                            modifierKeyCode == KeyMappings::SingleModifer ? 1 : 0;

    auto calculatedPoint = point*pointMultiplier;

    auto currentScore = playerScore(_setIndex);
    auto newScore = currentScore - calculatedPoint;

    // Evaluate input according to point domain and aggregated sum domain
    auto inputResponse = validateInput(newScore);

    if(inputResponse == InputPointDomain::InvalidDomain)
        throw INVALID_DOMAIN;

    if(inputResponse == AggregatedSumDomains::PointDomain)
    {
        // Update datacontext
        addPoint(calculatedPoint,newScore);
    }
    else if(inputResponse == AggregatedSumDomains::CriticalDomain)
    {
        addPoint(calculatedPoint,newScore);
    }
    else if(inputResponse == AggregatedSumDomains::TargetDomain &&
            (modifierKeyCode == terminateConditionModifier() || point == bullsEye))
    {
        //Winner declared
        declareWinner();
        addPoint(calculatedPoint,newScore);
    }
    else if(inputResponse == OutsideDomain || modifierKeyCode != terminateConditionModifier())
    {
        // Player made an 'overthrow' or didn't meet the winning terminate condition, and points is therefore nullified and added to datacontext
        addPoint(0,currentScore);
    }
}

void LocalFirstToPost::handleCurrentTournamentRequest()
{
    emit sendCurrentTournament(_currentTournament);
}

void LocalFirstToPost::recieveTournamentDetails(const QUuid &tournament,
                                                const int &keyPoint,
                                                const int &terminalKeyCode,
                                                const int &numberOfThrows,
                                                const PlayerPairs &assignedPlayerNames)
{
    _currentTournament = tournament;
    _keyPoint = keyPoint;
    _numberOfThrows = numberOfThrows;
    _assignedPlayerPairs = assignedPlayerNames;
    _currentStatus = ControllerState::InitializingIndexValues;
    pointLogisticInterface()->setLastThrowKeyCode(terminalKeyCode);
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
    _assignedUsernamesScore = playerScores;
    _currentStatus = ControllerState::Initialized;

    emit transmitResponse(ControllerResponse::isInitializedAndReady,{});
}

void LocalFirstToPost::confirmScoreRecieved(const QUuid &playerID, const QUuid &score)
{

}

void LocalFirstToPost::sendCurrentTurnValues()
{
    auto canUndo = canUndoTurn();
    auto canRedo = canRedoTurn();
    auto currentRound = currentRoundIndex();
    auto currentUserName = currentActiveUser();
    auto score = playerScore(currentSetIndex());
    auto throwSuggestion = pointLogisticInterface()->throwSuggestion(score,currentThrowIndex() + 1);
    emit transmitResponse(ControllerResponse::isInitializedAndReady,{canUndo,canRedo,currentRound,currentUserName,throwSuggestion});
}

QString LocalFirstToPost::currentActiveUser()
{
    auto pair = _assignedPlayerPairs.value(currentSetIndex());
    auto playerName = pair.second;
    return playerName;
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
        QVariantList arguments = {currentTournamentID(),currentActiveUser(),currentRoundIndex(),0,currentThrowIndex(),ModelDisplayHint::HiddenHint};
        // TODO: Implement signal to notify datacontext
        return _assignedPlayerPairs.value(_setIndex).first;
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
    QVariantList arguments = {currentTournamentID(),currentActiveUser(),currentRoundIndex(),0,currentThrowIndex(),ModelDisplayHint::HiddenHint};
    /*
     * Implement alternative to:
     *  - emit sendRequestToContext(ControllerRequest::RequestSetModelHint,arguments);
     */
    return _assignedPlayerPairs.at(_setIndex).first;
}

QUuid LocalFirstToPost::redoTurn()
{
    if(_turnIndex >= _totalTurns)
        return QUuid();
    else if(status() == ControllerState::WinnerDeclared)
        return QUuid();

    auto currentActiveUser = this->currentActiveUser();
    auto currentRoundIndex = this->currentRoundIndex();
    auto currentThrowIndex = this->currentThrowIndex();
    auto currentSetIndex = this->currentSetIndex();

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
    QVariantList arguments = {currentTournamentID(),currentActiveUser,currentRoundIndex,currentSetIndex,currentThrowIndex,ModelDisplayHint::DisplayHint};
    /*
     * TODO:
     * Implement alternative:
     *  emit sendRequestToContext(ControllerRequest::RequestSetModelHint,arguments);
     */

    return _assignedPlayerPairs.at(_setIndex).first;
}

void LocalFirstToPost::restartGame()
{
    _currentStatus = ControllerState::resetState;
    /*
     * TODO:
     * Implement alternative to:
     *  - emit sendRequestToContext(ControllerRequest::RequestResetTournament,{currentTournamentID()});
     */
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

int LocalFirstToPost::validateInput(const int &currentScore)
{
    auto minimumAllowedScore = terminateConditionModifier() == KeyMappings::SingleModifer ?
                1 : KeyMappings::DoubleModifier ?
                    2 : 3;
    if(currentScore > criticalLimit)
        return PointDomain;
    else if(currentScore <= criticalLimit && currentScore > minimumAllowedScore)
        return CriticalDomain;
    else if(currentScore == 0)
        return TargetDomain;
    else
        return OutsideDomain;
}

void LocalFirstToPost::addPoint(const int &point, const int &score)
{
    auto tournamentID = currentTournamentID();
    auto playerName = currentActiveUser();
    auto roundIndex = currentRoundIndex();
    auto setIndex = currentPlayerIndex();
    auto throwIndex = currentThrowIndex();
    QVariantList arguments = {tournamentID,playerName,roundIndex,setIndex,throwIndex, point, score};
    /*
     * TODO:
     * Implement alternative to:
     *  - emit sendRequestToContext(ControllerRequest::RequestStorePoint,arguments);
     */
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
    if(status() == ControllerState::AddScoreState)
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
    else
        emit transmitResponse(_currentStatus,{});
}

void LocalFirstToPost::nextTurn()
{
    incrementTurnIndexes();

    if(_turnIndex % _numberOfThrows == 0)
    {
        _setIndex++;
        _throwIndex = 0;
        if(_setIndex >= _assignedPlayerPairs.count()){
            _roundIndex++;
            _setIndex = 0;
        }
        _currentStatus = ControllerState::UpdateContextState;
        QVariantList arguments = {currentTournamentID(),currentActiveUser(),currentRoundIndex(),currentSetIndex()};
        /*
         * TODO:
         * Implement alternative to:
         *  - emit sendRequestToContext(ControllerRequest::RequestUpdateModelState,arguments);
         */
    }
    else
    {
        _throwIndex++;
        _currentStatus = ControllerState::AwaitsInput;
        sendCurrentTurnValues();
    }
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
    auto score = _assignedUsernamesScore.at(index);
    return score;
}

void LocalFirstToPost::setPlayerScore(const int &index, const int &newScore)
{
    _assignedUsernamesScore.replace(index,newScore);
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

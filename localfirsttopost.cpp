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

void LocalFirstToPost::handleRequestFromContext(const int &request, const QVariantList &args)
{
    if(request == DataContextRequests::RequestCurrentTournament)
    {
        emit sendResponseToContext(ControllerResponse::DataProvidedSuccess,{currentTournamentID()});
    }
}

void LocalFirstToPost::handleResponseFromContext(const int &response, const QVariantList &args)
{
    if(status() == ControllerState::InitializingBasicValues && response == DataContextResponse::DataRequestSuccess)
    /*
     * Phase I - Basic values request
     *  - Controller is in its initializing phase where it needs basic values
     *  - Datacontext has responded ok and has passed the requested values
     */
    {
        _currentTournament = args[0].toUuid();
        _keyPoint = args[1].toInt();
        auto lastThrowKeyCode = args[2].toInt();
        _numberOfThrows = args[3].toInt();
        _assignedUserNames = args[4].toStringList();
        _currentStatus = ControllerState::InitializingIndexValues;

        pointLogisticInterface()->setLastThrowKeyCode(lastThrowKeyCode);
        emit sendRequestToContext(ControllerRequest::RequestIndexValues,{_currentTournament,_assignedUserNames});
    }
    else if(status() == ControllerState::InitializingIndexValues && response == DataContextResponse::DataRequestSuccess)
    /*
     * Phase II - Controller indexes request
     *  - Controller is in its initializing phase where it needs its indexes updated
     *  - Datacontext has responded ok and has passed the requested indexes
     */
    {
        _roundIndex = args[0].toInt();
        _setIndex = args[1].toInt();
        _throwIndex = args[2].toInt();
        _turnIndex = args[3].toInt();
        _totalTurns = args[4].toInt();

        _currentStatus = ControllerState::InitializingPlayerScores;
        emit sendRequestToContext(ControllerRequest::RequestPlayerScores,{_currentTournament,_assignedUserNames});
    }
    else if(status() == ControllerState::InitializingPlayerScores && response == DataContextResponse::DataRequestSuccess)
    /*
     * Phase III - Playerscores requested
     *  - The controller has requested playerscores
     *  - Datacontext has responded ok and passed the requested scores
     *  - The controller is now considered initialized and is ready to start
     */
    {
        auto scores = args[0].value<QList<int>>();
        _assignedUsernamesScore = scores;
        _currentStatus = ControllerState::Initialized;
        emit transmitResponse(ControllerResponse::isReadyAndAwaits,{});
    }
    else if(status() == ControllerState::AddScoreState && response == DataContextResponse::UpdateSuccessfull)
    /*
     *  - Controller has prior to this event transmitted a score to datacontext
     *  - Datacontext responds ok
     *      > Which indicates it has succesfully stored the score
     *      > And removed scoremodels associated with current tournament with hidden display hint
     *  - Controller sets its indexes according to the above
     */
    {
        _totalTurns = _turnIndex;
        auto playerName = currentActiveUser();
        auto pointValue = args[0].toInt();
        auto scoreValue = args[1].toInt();

        setPlayerScore(currentPlayerIndex(),scoreValue);
        emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,pointValue,scoreValue});
    }
    else if(status() == ControllerState::UpdateContextState && response == DataContextResponse::UpdateSuccessfull)
    {
        _currentStatus = ControllerState::AwaitsInput;
        sendCurrentTurnValues();
    }
    else if(status() == ControllerState::UndoState && response == DataContextResponse::UpdateSuccessfull)
    {
        auto playerName = args.first();
        auto dimmedPointValue = args.at(2).toInt();
        auto dimmedScoreValue = args.at(3).toInt();
        auto previousScore = dimmedScoreValue + dimmedPointValue;
        setPlayerScore(currentPlayerIndex(),previousScore);
        emit transmitResponse(ControllerResponse::ScoreRemove,{playerName});
    }
    else if(status() == ControllerState::RedoState && response == DataContextResponse::UpdateSuccessfull)
    {
        auto playerName = args[0].toString();
        auto setIndex = args[1].toInt();
        auto pointValue = args[2].toInt();
        auto scoreValue = args[3].toInt();
        setPlayerScore(setIndex,scoreValue);
        emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,pointValue,scoreValue});
    }
    else if(status() == ControllerState::WinnerDeclared && response == DataContextResponse::UpdateSuccessfull)
    {
        auto winnerName = determinedWinnerName();
        emit transmitResponse(ControllerResponse::WinnerFound,{winnerName});
    }
    else if(status() == ControllerState::resetState && response == DataContextResponse::UpdateSuccessfull)
        /*
         *  Phase IV - Reset requested
         *  - Controller has requested models associated with its current tournament removed
         *  - Now controller needs to reinitialize with request for basic values, indexes and playerscores
         */
    {
        _currentStatus = ControllerState::InitializingBasicValues;
        emit sendRequestToContext(ControllerRequest::RequestBasicValues,{_currentTournament,_assignedUserNames});
    }
}

void LocalFirstToPost::sendCurrentTurnValues()
{
    auto canUndo = canUndoTurn();
    auto canRedo = canRedoTurn();
    auto currentRound = currentRoundIndex();
    auto currentUserName = currentActiveUser();
    auto score = playerScore(currentSetIndex());
    auto throwSuggestion = pointLogisticInterface()->throwSuggestion(score,currentThrowIndex() + 1);
    emit transmitResponse(ControllerResponse::isReadyAndAwaits,{canUndo,canRedo,currentRound,currentUserName,throwSuggestion});
}

QString LocalFirstToPost::currentActiveUser()
{
    auto playerName = _assignedUserNames.value(currentSetIndex());
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
        emit sendRequestToContext(ControllerRequest::RequestSetModelHint,arguments);
        return _assignedUserNames.value(_setIndex);
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
    emit sendRequestToContext(ControllerRequest::RequestSetModelHint,arguments);
    return _assignedUserNames.at(_setIndex);
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
    emit sendRequestToContext(ControllerRequest::RequestSetModelHint,arguments);

    return _assignedUserNames.value(_setIndex);
}

void LocalFirstToPost::restartGame()
{
    _currentStatus = ControllerState::resetState;
    emit sendRequestToContext(ControllerRequest::RequestResetTournament,{currentTournamentID()});
}

void LocalFirstToPost::setCurrentTournament(const int &index)
{
    _currentStatus = ControllerState::InitializingBasicValues;
    emit sendRequestToContext(ControllerRequest::RequestBasicValues,{index});
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
    emit sendRequestToContext(ControllerRequest::RequestStorePoint,arguments);
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
        if(_setIndex >= _assignedUserNames.count()){
            _roundIndex++;
            _setIndex = 0;
        }
        _currentStatus = ControllerState::UpdateContextState;
        QVariantList arguments = {currentTournamentID(),currentActiveUser(),currentRoundIndex(),currentSetIndex()};
        emit sendRequestToContext(ControllerRequest::RequestUpdateModelState,arguments);
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

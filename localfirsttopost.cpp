#include "localfirsttopost.h"

void LocalFirstToPost::start()
{
    if(_currentStatus != ControllerState::Initialized)
    {
        transmitResponse(ControllerState::NotInitialized,{});
        return;
    }
    _isActive = true;
    _currentStatus = ControllerState::AwaitsInput;
    transmitResponse(_currentStatus,{canUndoTurn(),canRedoTurn(),currentRoundIndex(),currentActiveUser()});
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

    auto pointMultiplier = modifierKeyCode == 0x2C ? 3 :
                            modifierKeyCode == 0x2B ? 2 :
                            modifierKeyCode == 0x2A ? 1 : 0;

    auto calculatedPoint = point *pointMultiplier;

    auto currentScore = playerScore(_setIndex);
    auto newScore = currentScore - calculatedPoint;

    // Evaluate input according to point domain and aggregated sum domain
    auto inputResponse = validateInput(newScore);

    if(inputResponse == InputPointDomain::InvalidDomain)
        throw INVALID_DOMAIN;

    if(inputResponse == AggregatedSumDomains::PointDomain)
    {
        // Update datacontext
        addPoint(point,newScore);
    }
    else if(inputResponse == AggregatedSumDomains::CriticalDomain)
    {
        addPoint(point,newScore);
    }
    else if(inputResponse == AggregatedSumDomains::TargetDomain && modifierKeyCode == terminateConditionModifier())
    {
        // Winner declared
        declareWinner();
        addPoint(point,newScore);
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
    {
        _currentTournament = args[0].toUuid();
        _keyPoint = args[1].toInt();
        _terminateConditionModifier = args[2].toInt();
        _numberOfThrows = args[3].toInt();
        _assignedUserNames = args[4].toStringList();

        _currentStatus = ControllerState::InitializingIndexValues;

        emit sendRequestToContext(ControllerRequest::RequestIndexValues,{_currentTournament,_assignedUserNames});
    }
    else if(status() == ControllerState::InitializingIndexValues && response == DataContextResponse::DataRequestSuccess)
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
     * The controller has been initialized and is ready to launch
     */
    {
        auto scores = args[0].value<QList<int>>();
        _assignedUsernamesScore = scores;
        _currentStatus = ControllerState::Initialized;
        emit transmitResponse(ControllerResponse::isReadyAndAwaits,{});
    }
    else if(status() == ControllerState::AddScoreState && response == DataContextResponse::UpdateSuccessfull)
    /*
     *  - Datacontext responds it has successfully created a scoremodel and added it to its database
     *  - Controller transmits current username and score to UI context
     */
    {
        auto playerName = currentActiveUser();
        auto scoreValue = playerScore(currentPlayerIndex());
        emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,scoreValue});
    }
    else if(status() == ControllerState::UpdateContextState && response == DataContextResponse::UpdateSuccessfull)
    {
        _currentStatus = ControllerState::AwaitsInput;
        sendCurrentTurnValues();
    }
    else if(status() == ControllerState::UndoState && response == DataContextResponse::UpdateSuccessfull)
    {
        auto playerName = args.first();
        auto dimmedPointValue = args.at(1).toInt();
        auto dimmedScoreValue = args.at(2).toInt();
        auto previousScore = dimmedScoreValue + dimmedPointValue;
        setPlayerScore(currentPlayerIndex(),previousScore);
        emit transmitResponse(ControllerResponse::ScoreRemove,{playerName});
    }
    else if(status() == ControllerState::RedoState && response == DataContextResponse::UpdateSuccessfull)
    {
        auto playerName = args.at(0);
        auto scoreValue = args.at(2).toInt();
        setPlayerScore(currentPlayerIndex(),scoreValue);
        emit transmitResponse(ControllerResponse::ScoreTransmit,{playerName,scoreValue});
    }
    else if(status() == ControllerState::WinnerDeclared && response == DataContextResponse::UpdateSuccessfull)
    {
        auto winnerName = determinedWinnerName();
        emit transmitResponse(ControllerResponse::WinnerFound,{winnerName});
    }
    else if(status() == ControllerState::resetState && response == DataContextResponse::UpdateUnSuccessfull)
    {
        _currentStatus = ControllerState::InitializingIndexValues;
        emit sendRequestToContext(ControllerRequest::RequestIndexValues,{_currentTournament,_assignedUserNames});
    }
}

void LocalFirstToPost::sendCurrentTurnValues()
{
    auto canUndo = canUndoTurn();
    auto canRedo = canRedoTurn();
    auto currentRound = currentRoundIndex();
    auto currentUserName = currentActiveUser();
    emit transmitResponse(_currentStatus,{canUndo,canRedo,currentRound,currentUserName});
}

QString LocalFirstToPost::playerMessage()
{
    /* This is the hard part
         * TODO: Declare a QString variabel holding a message
         * TODO: Find some algorithm to determine possible ways to win within 3 or less attemps
         */
    return QString();
}

QString LocalFirstToPost::calculateThrowSuggestion(const int &score)
{
    /* TODO: Here you first have to develop an algorithm to help assess the various combinations that exists after the player reach the 180 points threshold
     * TODO: When done, ruct a string containing the various suggestions. Ex.: 'T20,D10,5' or 'D5,1' for a remaining score at 95 or 11 respectively.
     */

    auto legCount = _numberOfThrows;

    auto remainingScore = _keyPoint - score;

    auto msg = _pointLogisticInterface->constructThrowSuggestions(remainingScore,legCount);

    return msg;
}

QString LocalFirstToPost::currentActiveUser()
{
    auto playerID = _assignedUserNames.value(_setIndex);
    return playerID;
}

QUuid LocalFirstToPost::undoTurn()
{
    if(_turnIndex <= 0)
        return QUuid();

    _currentStatus = ControllerState::UndoState;

    _turnIndex--;
    if(_throwIndex > 0)
    {
        _throwIndex--;
        QVariantList arguments = {currentTournamentID(),currentActiveUser(),currentRoundIndex(),currentThrowIndex(),ModelDisplayHint::HiddenHint};
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
    QVariantList arguments = {currentTournamentID(),currentActiveUser(),currentRoundIndex(),currentThrowIndex(),ModelDisplayHint::HiddenHint};
    emit sendRequestToContext(ControllerRequest::RequestSetModelHint,arguments);
    return _assignedUserNames.at(_setIndex);
}

QUuid LocalFirstToPost::redoTurn()
{
    if(_turnIndex >= _totalTurns)
        return QUuid();

    auto currentActiveUser = this->currentActiveUser();
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
    QVariantList arguments = {currentTournamentID(),currentActiveUser,currentRoundIndex,currentThrowIndex,ModelDisplayHint::DisplayHint};
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
    return _turnIndex > 0;
}

bool LocalFirstToPost::canRedoTurn()
{
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
    if(currentScore > criticalLimit)
        return PointDomain;
    else if(currentScore <= criticalLimit && currentScore > 0)
        return CriticalDomain;
    else if(currentScore <= 0)
        return TargetDomain;
    else
        return OutsideDomain;
}

void LocalFirstToPost::addPoint(const int &point, const int &score)
{
    setPlayerScore(currentPlayerIndex(),score);
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

void LocalFirstToPost::handleControllerStateRequest()
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
    return _terminateConditionModifier;
}

IPointLogisticManager<QString> *LocalFirstToPost::pointLogisticInterface() const
{
    return _pointLogisticInterface;
}

AbstractGameController *LocalFirstToPost::setPointLogisticInterface(IPointLogisticManager<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void LocalFirstToPost::consistencyCheck()
{
    Q_UNIMPLEMENTED();
}

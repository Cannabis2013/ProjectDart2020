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
    else if(inputResponse == AggregatedSumDomains::TargetDomain)
    {
        // Winner declared
        declareWinner();
        addPoint(point,newScore);
    }
    else if(inputResponse == OutsideDomain)
    {
        // Player made an 'overthrow' and points is nullified and added to datacontext
        addPoint(0,currentScore);
    }
}

void LocalFirstToPost::handleRequestFromContext(const int &context, const int &request, const QVariantList &args)
{

}

void LocalFirstToPost::handleResponseFromContext(const int &context, const int &response, const QVariantList &args)
{
    if(context != ContextCodes::DataContext)
        return;

    if(status() == ControllerState::InitializingBasicValues && response == DataContextResponse::DataRequestSuccess)
    {
        _currentTournament = args[0].toUuid();
        _keyPoint = args[1].toInt();
        _numberOfThrows = args[2].toInt();
        _assignedUserNames = args[3].toStringList();

        _currentStatus = ControllerState::InitializingIndexValues;

        emit sendRequestToDataContext(ContextCodes::ControllerContext,
                                      ControllerRequest::RequestIndexValues,{_currentTournament,_assignedUserNames});
    }
    else if(status() == ControllerState::InitializingIndexValues && response == DataContextResponse::DataRequestSuccess)
    {
        _roundIndex = args[0].toInt();
        _setIndex = args[1].toInt();
        _throwIndex = args[2].toInt();
        _turnIndex = args[3].toInt();
        _totalTurns = args[4].toInt();

        _currentStatus = ControllerState::InitializingPlayerScores;
        emit sendRequestToDataContext(ContextCodes::ControllerContext,
                                      ControllerRequest::RequestPlayerScores,{_currentTournament,_assignedUserNames});
    }
    else if(status() == ControllerState::InitializingPlayerScores && response == DataContextResponse::DataRequestSuccess)
    {
        auto scores = args[0].value<QList<int>>();
        _assignedUsernamesScore = scores;
        _currentStatus = ControllerState::Initialized;
        transmitResponse(ControllerResponse::isInitializedAndWaitsRequest,{});
    }
}

void LocalFirstToPost::sendCurrentTurnValues()
{
    auto canUndo = canUndoTurn();
    auto canRedo = canRedoTurn();
    auto currentRound = currentRoundIndex();
    auto currentUserName = currentActiveUser();
    transmitResponse(_currentStatus,{canUndo,canRedo,currentRound,currentUserName});
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
        emit requestSetScoreHint(currentTournamentID(),currentActiveUser(),currentRoundIndex(),currentThrowIndex(),ModelDisplayHint::HiddenHint);
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
    emit requestSetScoreHint(currentTournamentID(),currentActiveUser(),currentRoundIndex(),currentThrowIndex(),ModelDisplayHint::HiddenHint);
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

    emit requestSetScoreHint(currentTournamentID(),currentActiveUser,currentRoundIndex,currentThrowIndex,ModelDisplayHint::DisplayHint);
    return _assignedUserNames.value(_setIndex);
}

void LocalFirstToPost::setCurrentTournament(const int &index)
{
    _currentStatus = ControllerState::InitializingBasicValues;
    emit sendRequestToDataContext(ContextCodes::ControllerContext,ControllerRequest::RequestBasicValues,{index});
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
    else if(currentScore == 0)
        return TargetDomain;
    else
        return OutsideDomain;
}

void LocalFirstToPost::addPoint(const int &point, const int &score)
{
    setPlayerScore(currentPlayerIndex(),score);
    auto playerID = currentActiveUser();
    auto tournamentID = currentTournamentID();
    auto roundIndex = currentRoundIndex();
    auto setIndex = currentPlayerIndex();
    auto throwIndex = currentThrowIndex();

    emit sendPoint(tournamentID,playerID,roundIndex,setIndex,throwIndex,point,score);
}

void LocalFirstToPost::handleCurrentTournamentRequest()
{
    emit sendCurrentTournament(_currentTournament);
}

void LocalFirstToPost::handleResponseFromDataContext(const int &response, const QVariantList &args)
{
    if(response == DataContextResponse::UpdateSuccessfull && this->status() == ControllerState::UpdateContextState)
    /*
     * The controller has updated datacontext with either, or both, a new round or set
     */
    {
        _currentStatus = ControllerState::AwaitsInput;
        sendCurrentTurnValues();
    }
    else if(response == DataContextResponse::UpdateSuccessfull && this->status() == ControllerState::NotInitialized)
    /*
     * The controller has been initialized and is ready to launch
     */
    {
        _currentStatus = ControllerState::Initialized;
        transmitResponse(this->status(),{});
    }
    else if(response == DataContextResponse::UpdateSuccessfull && this->status() == ControllerState::AddScoreState)
    /*
     * The controller is in a state where it has updated the datacontext with score/point values
     *  and needs to send the score back to the UI
     */
    {
        auto userName = currentActiveUser();
        auto scoreValue = playerScore(currentPlayerIndex());
        transmitResponse(ControllerResponse::ScoreTransmit,{userName,scoreValue});
    }
    else if(response == DataContextResponse::UpdateSuccessfull && this->status() == ControllerState::UndoState)
    /*
     * The controller is in a undo state where it has altered its indexes
     *  and needs to notify the UI which user is affected by this alteration
     */
    {
        auto userName = args.first();
        auto dimmedPointValue = args.at(1).toInt();
        auto dimmedScoreValue = args.at(2).toInt();
        auto previousScore = dimmedScoreValue + dimmedPointValue;
        setPlayerScore(currentPlayerIndex(),previousScore);
        emit transmitResponse(ControllerResponse::ScoreRemove,{userName});
    }
    else if(response == DataContextResponse::UpdateSuccessfull && this->status() == ControllerState::RedoState)
        /*
         * The controller is in a redo state where it has altered its indexes
         *  and needs to notify the UI which user is affected by this alteration
         */
    {
        auto userName = args.at(0);
        auto scoreValue = args.at(2).toInt();
        setPlayerScore(currentPlayerIndex(),scoreValue);
        emit transmitResponse(ControllerResponse::ScoreTransmit,{userName,scoreValue});
    }
    else if(response == DataContextResponse::UpdateUnSuccessfull && this->status() == ControllerState::WinnerDeclared)
    {
        transmitResponse(_currentStatus,{determinedWinner()});
        _isActive = false;
    }
    else if(response == DataContextResponse::UpdateUnSuccessfull && isActive())
    /*
     * Something is wrong. Probably there is some inconsistencies involving models
     *  which is related to another models that does not exists anymore.
     */
    {
        _isActive = false;
        _currentStatus = ControllerState::Inconsistency;
        emit transmitResponse(ControllerResponse::InconsistencyDetected,{});
    }
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
    else if(this->status() == ControllerState::UndoState)
    {
        _currentStatus = ControllerState::AwaitsInput;
        sendCurrentTurnValues();
    }
    else if(this->status() == ControllerState::RedoState)
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
        emit sendCurrentIndexes(currentTournamentID(),currentActiveUser(),currentRoundIndex(),currentSetIndex());
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

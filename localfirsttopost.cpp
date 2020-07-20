#include "localfirsttopost.h"

int LocalFirstToPost::start()
{
    _isActive = true;
    if(_roundIndex == 0){
        emit addRound(currentTournamentID(),++_roundIndex);
        emit addSet(currentTournamentID(),currentRoundIndex(),currentLegIndex());
    }
    _currentStatus = GameStatus::GameControllerAwaitsInput;
    emit sendStatus(_currentStatus,{});
    return _currentStatus;
}

int LocalFirstToPost::stop()
{
    _isActive = false;
    _currentStatus = GameStatus::GameControllerStopped;
    emit sendStatus(_currentStatus,{});
    return _currentStatus;
}

int LocalFirstToPost::processInput(const int &point, const int &currentScore)
{
    if(status() == GameControllerIdle ||
            status() == GameControllerStopped ||
            status() == GameControllerWinnerDeclared)
    {
        emit sendStatus(status(),{});
        return status();
    }

    _currentStatus = GamecontrollerBusy;

    auto score = currentScore + point;

    // Evaluate input according to point domain and aggregated sum domain
    auto inputResponse = validateInput(point,score);

    if(inputResponse == InputPointDomain::InvalidDomain)
        throw INVALID_DOMAIN;

    if(inputResponse == AggregatedSumDomains::PointDomain)
    {
        // Update datacontext
        addPoint(point);
        _currentStatus = GameStatus::GameControllerAwaitsInput;
    }
    else if(inputResponse == AggregatedSumDomains::CriticalDomain)
    {
        addPoint(point);
        _currentStatus = GameStatus::GameControllerAwaitsInput;
    }
    else if(inputResponse == AggregatedSumDomains::TargetDomain)
    {
        // Winner declared
        addPoint(0);
        declareWinner();

        return status();
    }
    else if(inputResponse == OutsideDomain)
    {
        // Player made an 'overthrow' and points is nullified and added to datacontext
        addPoint(0);
    }

    nextTurn(); // Initialize next turn. Increment playerindex if necessary. A new set or round is added respectively if necessary.

    /*
     * Determine current state after post increment of gamestate variables
     */
    /*
    auto currentState = validateCurrentState();
    if(currentState == CriticalDomain)
        calculateThrowSuggestion();
    */

    emit sendStatus(_currentStatus,{});
    emit stateChanged();

    return status();
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

QUuid LocalFirstToPost::currentActivePlayer()
{
    auto playerID = _assignedPlayers.value(_setIndex);
    return playerID;
}

int LocalFirstToPost::currentRoundIndex()
{
    return _roundIndex;
}

int LocalFirstToPost::currentPlayerIndex()
{
    return _setIndex;
}

int LocalFirstToPost::currentSetIndex()
{
    return _setIndex;
}

int LocalFirstToPost::currentLegIndex()
{
    return _throwIndex;
}

QUuid LocalFirstToPost::currentTournamentID()
{
    return _currentTournament;
}

int LocalFirstToPost::status()
{
    return _currentStatus;
}

int LocalFirstToPost::lastPlayerIndex()
{
    return _assignedPlayers.count() - 1;
}

int LocalFirstToPost::playerIndex()
{
    return _setIndex;
}

QUuid LocalFirstToPost::determinedWinner()
{
    return _winner;
}

QUuid LocalFirstToPost::undoTurn()
{
    if(_turnIndex <= 0)
        throw UNABLE_TO_ALTER_TURN;

    _turnIndex--;
    if(_throwIndex > 0)
    {
        _throwIndex--;
        return _assignedPlayers.value(_setIndex);
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

    return _assignedPlayers.value(_setIndex);
}

QUuid LocalFirstToPost::redoTurn()
{
    if(_turnIndex >= _totalTurns)
        throw UNABLE_TO_ALTER_TURN;

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

    return _assignedPlayers.value(_setIndex);
}

bool LocalFirstToPost::canUndoTurn()
{
    return _turnIndex > 0;
}

bool LocalFirstToPost::canRedoTurn()
{
    return _turnIndex < _totalTurns;
}

void LocalFirstToPost::initializeController(const QUuid &tournament, const int &keyPoint, const int &numberOfThrows, QList<QUuid> assignedPlayers)
{
    _currentTournament = tournament;
    _keyPoint = keyPoint;
    _numberOfThrows = numberOfThrows;
    _assignedPlayers = assignedPlayers;

    emit requestInitialIndexes(_currentTournament,&_assignedPlayers);
}


int LocalFirstToPost::validateCurrentState(const int &score)
{
    auto playerSum = _keyPoint - score;

    if(playerSum > criticalLimit)
        return PointDomain;
    else if(playerSum <= criticalLimit && playerSum > 0)
        return CriticalDomain;
    else if(playerSum == 0)
        return TargetDomain;
    else
        return OutsideDomain;
}

int LocalFirstToPost::validateInput(const int &pointValue, const int &currentScore)
{
    auto playerScore = _keyPoint - currentScore;

    if(playerScore > criticalLimit)
        return PointDomain;
    else if(playerScore <= criticalLimit && playerScore > 0)
        return CriticalDomain;
    else if(playerScore == 0)
        return TargetDomain;
    else
        return OutsideDomain;
}

void LocalFirstToPost::addPoint(const int &point)
{
    auto playerID = currentActivePlayer();
    auto tournamentID = currentTournamentID();
    auto roundIndex = currentRoundIndex();
    auto setIndex = currentPlayerIndex();
    auto legIndex = currentLegIndex();

    emit sendPoint(tournamentID,playerID,roundIndex,setIndex,legIndex,point);
}


void LocalFirstToPost::initializeIndexes(const int &roundIndex,
                                         const int &setIndex,
                                         const int &throwIndex,
                                         const int &turnIndex,
                                         const int &totalTurns)
{
    _roundIndex = roundIndex;
    _setIndex = setIndex;
    _throwIndex = throwIndex;
    _turnIndex = turnIndex;
    _totalTurns = totalTurns;

    _currentStatus = GameStatus::GameControllerInitialized;

    emit sendStatus(_currentStatus,{});
}

void LocalFirstToPost::handleCurrentTournamentRequest()
{
    emit sendCurrentTournament(_currentTournament);
}

void LocalFirstToPost::recieveStatus(const int &status, const QVariantList &args)
{

}

void LocalFirstToPost::handleReplyFromContext(const int &status)
{
    if(status == Status::ContextSuccessfullyUpdated && !isActive())
        _currentStatus = GameStatus::GameControllerInitialized;
    else if(status == Status::ContextSuccessfullyUpdated && isActive())
        _currentStatus = GameStatus::GameControllerAwaitsInput;
}

bool LocalFirstToPost::isActive()
{
    return _isActive;
}

int LocalFirstToPost::currentTurnIndex()
{
    return _turnIndex;
}

bool LocalFirstToPost::isIndexOffset()
{
    return _isOff;
}

void LocalFirstToPost::nextTurn()
{
    incrementTurnIndexes();

    if(_turnIndex % _numberOfThrows == 0)
    {
        _setIndex++;
        _throwIndex = 0;
        if(_setIndex >= _assignedPlayers.count()){
            emit addRound(currentTournamentID(),++_roundIndex);
            _setIndex = 0;
        }
        emit addSet(currentTournamentID(),currentRoundIndex(),_setIndex);
    }
    else
    {
        _throwIndex++;
    }
}

void LocalFirstToPost::declareWinner()
{
    _winner = currentActivePlayer();
    _isActive = false;
    _currentStatus = GameControllerWinnerDeclared;
}

void LocalFirstToPost::incrementTurnIndexes()
{
    if(_turnIndex == _totalTurns)
        _totalTurns++;
    _turnIndex++;
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

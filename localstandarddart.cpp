#include "localstandarddart.h"


LocalStandardDart::LocalStandardDart()
{
}

QUuid LocalStandardDart::start()
{
    _isActive = true;

    dataContext()->addRound(currentTournament(),++_roundIndex);
    auto setID = dataContext()->addSet(currentTournament(),_roundIndex,_playerIndex);

    return setID;
}

void LocalStandardDart::stop()
{
    _isActive = false;
}

int LocalStandardDart::processInput(const int &point)
{
    if(status() == (Idle | WinnerDeclared))
        return status();

    auto inputResponse = validateInput(point);

    if(inputResponse == InputState::PointDomain)
    {
        addPoint(point);
    }
    else if(inputResponse == InputState::TargetDomain)
    {
        // Winner declared
        declareWinner();

        return status();
    }
    else if(inputResponse == OutsideDomain)
    {
        // Player made an 'overthrow' and points is nullified and added to datacontext
        addPoint(0);
    }

    nextTurn(); // Initialize next turn. Increment playerindex if necessary. A new set or round is added respectively if necessary.

    // Determine current state after post increment of gamestate variables
    auto currentState = validateCurrentState();
    if(currentState == CriticalDomain)
        calculateThrowSuggestion();

    return status();
}

QString LocalStandardDart::playerMessage() const
{
    /* This is the hard part
         * TODO: Declare a QString variabel holding a message
         * TODO: Find some algorithm to determine possible ways to win within 3 or less attemps
         */
    return QString();
}

QString LocalStandardDart::calculateThrowSuggestion() const
{
    /* TODO: Here you first have to develop an algorithm to help assess the various combinations that exists after the player reach the 180 points threshold
     * TODO: When done, construct a string containing the various suggestions. Ex.: 'T20,D10,5' or 'D5,1' for a remaining score at 95 or 11 respectively.
     */

    return QString();
}

QUuid LocalStandardDart::currentActivePlayer() const
{
    return _assignedPlayers.value(_playerIndex);
}

int LocalStandardDart::currentRoundIndex() const
{
    return _roundIndex;
}

int LocalStandardDart::currentPlayerIndex() const
{
    return _playerIndex;
}

int LocalStandardDart::currentLegIndex() const
{
    return _legIndex;
}

QUuid LocalStandardDart::currentTournament() const
{
    return _tournament;
}

int LocalStandardDart::status() const
{
    return _currentStatus;
}

int LocalStandardDart::lastPlayerIndex() const
{
    return _assignedPlayers.count() - 1;
}

int LocalStandardDart::playerIndex() const
{
    return _playerIndex;
}

QUuid LocalStandardDart::determinedWinner() const
{
    return _winner;
}

QUuid LocalStandardDart::undoTurn()
{
    if(_turnIndex <= 0)
        throw "Unable to unddo turn";

    if(_legIndex > 0)
    {
        _legIndex--;
        _turnIndex--;

        return _assignedPlayers.value(_playerIndex);
    }

    _legIndex = 2;

    if(_playerIndex == 0)
    {
        _playerIndex = lastPlayerIndex();
        _roundIndex--;
    }
    else
    {
        _playerIndex--;
    }

    return _assignedPlayers.value(_playerIndex);
}

QUuid LocalStandardDart::redoTurn()
{
    if(_turnIndex >= _totalTurns)
        throw "Unable to unddo turn";

    if(_legIndex < _numberOfLegs)
        _legIndex++;
    else
        _legIndex = 0;

    if(_playerIndex == lastPlayerIndex())
    {
        _playerIndex = 0;
        _roundIndex++;
    }
    else
    {
        _playerIndex++;
    }

    _turnIndex++;
}

void LocalStandardDart::setDataContext(DefaultDataInterface *dataContext)
{
    _dataContext = dataContext;
}

DefaultDataInterface *LocalStandardDart::dataContext()
{
    return _dataContext;
}

LocalStandardDart::InputState LocalStandardDart::validateCurrentState()
{
    auto playerSum = sum();

    if(playerSum > criticalLimit)
        return PointDomain;
    else if(playerSum <= criticalLimit && playerSum > 0)
        return CriticalDomain;
    else if(playerSum == 0)
        return TargetDomain;
    else
        return OutsideDomain;
}

LocalStandardDart::InputState LocalStandardDart::validateInput(const int &pointValue)
{
    auto playerSum = sum(pointValue);

    if(playerSum > criticalLimit)
        return PointDomain;
    else if(playerSum <= criticalLimit && playerSum > 0)
        return CriticalDomain;
    else if(playerSum == 0)
        return TargetDomain;
    else
        return OutsideDomain;
}

QUuid LocalStandardDart::addPoint(const int &point)
{
    auto playerID = currentActivePlayer();
    auto tournamentID = currentTournament();
    auto roundIndex = currentRoundIndex();
    auto setIndex = currentPlayerIndex();
    auto legIndex = currentLegIndex();

    auto pointID = dataContext()->addPoint(tournamentID,
                                           roundIndex,
                                           setIndex,
                                           legIndex,
                                           point,
                                           playerID);


    return pointID;
}

int LocalStandardDart::currentTurnIndex() const
{
    return _turnIndex;
}

bool LocalStandardDart::isIndexOffset()
{
    return _isOff;
}

void LocalStandardDart::nextTurn()
{
    incrementTurnIndexes();

    if(_turnIndex % _numberOfLegs == 0)
    {
        _playerIndex++;
        _legIndex = 0;
        if(_playerIndex >= _assignedPlayers.count())
            dataContext()->addRound(currentTournament(),++_roundIndex);

        dataContext()->addSet(currentTournament(),currentRoundIndex(),_playerIndex);
    }
    else
    {
        _legIndex++;
    }
}

int LocalStandardDart::sum(const int &pointValue)
{
    auto pointIds = _dataContext->playerPoints(_tournament,currentActivePlayer());

    int sum = pointValue;

    for (auto pointId : pointIds)
        sum += _dataContext->pointValue(pointId);

    return sum;
}

int LocalStandardDart::sum(const QUuid &player)
{
    auto pointIds = _dataContext->playerPoints(_tournament,player);

    int sum = 0;
    for (auto pointId : pointIds)
        sum += _dataContext->pointValue(pointId);

    return sum;
}

int LocalStandardDart::sum()
{
    auto pointIds = _dataContext->playerPoints(_tournament,currentActivePlayer());

    int sum = 0;
    for (auto pointId : pointIds)
        sum += _dataContext->pointValue(pointId);

    return sum;
}

void LocalStandardDart::declareWinner()
{
    _winner = currentActivePlayer();
    _isActive = false;
    _currentStatus = WinnerDeclared;
}

void LocalStandardDart::incrementTurnIndexes()
{
    if(_turnIndex == _totalTurns)
        _totalTurns++;
    _turnIndex++;
}

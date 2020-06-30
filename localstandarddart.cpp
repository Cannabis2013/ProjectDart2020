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

    // Evaluate input according to point domain and aggregated sum domain
    auto inputResponse = validateInput(point);

    if(inputResponse == InputPointDomain::InvalidDomain)
    {
        throw INVALID_DOMAIN;
    }
    if(inputResponse == AggregatedSumDomain::PointDomain)
    {
        // Update datacontext
        addPoint(point);
    }
    else if(inputResponse == AggregatedSumDomain::TargetDomain)
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

QString LocalStandardDart::playerMessage()
{
    /* This is the hard part
         * TODO: Declare a QString variabel holding a message
         * TODO: Find some algorithm to determine possible ways to win within 3 or less attemps
         */
    return QString();
}

QString LocalStandardDart::calculateThrowSuggestion()
{
    /* TODO: Here you first have to develop an algorithm to help assess the various combinations that exists after the player reach the 180 points threshold
     * TODO: When done, ruct a string containing the various suggestions. Ex.: 'T20,D10,5' or 'D5,1' for a remaining score at 95 or 11 respectively.
     */

    auto legCount = dataContext()->tournamentNumberOfLegs(currentTournament());

    auto remainingScore = _keyPoint - sum();

    IPointLogisticManager<QString> *_pointLogisticInterface = new PointLogisticManager(legCount);

    auto msg = _pointLogisticInterface->constructThrowSuggestions(remainingScore,legCount);

    return msg;
}

QUuid LocalStandardDart::currentActivePlayer()
{
    return _assignedPlayers.value(_playerIndex);
}

int LocalStandardDart::currentRoundIndex()
{
    return _roundIndex;
}

int LocalStandardDart::currentPlayerIndex()
{
    return _playerIndex;
}

int LocalStandardDart::currentSetIndex()
{
    return _playerIndex;
}

int LocalStandardDart::currentLegIndex()
{
    return _legIndex;
}

QUuid LocalStandardDart::currentTournament()
{
    return _tournament;
}

void LocalStandardDart::setCurrentTournament(QUuid &tournament)
{
    _tournament = tournament;
}

int LocalStandardDart::status()
{
    return _currentStatus;
}

int LocalStandardDart::lastPlayerIndex()
{
    return _assignedPlayers.count() - 1;
}

int LocalStandardDart::playerIndex()
{
    return _playerIndex;
}

QUuid LocalStandardDart::determinedWinner()
{
    return _winner;
}

QUuid LocalStandardDart::undoTurn()
{
    if(_turnIndex <= 0)
        throw UNABLE_TURN;

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
        throw UNABLE_TURN;

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

    return _assignedPlayers.value(_playerIndex);
}

void LocalStandardDart::setDataContext(DefaultDataInterface *dataContext)
{
    _dataContext = dataContext;
}

DefaultDataInterface *LocalStandardDart::dataContext()
{
    return _dataContext;
}

int LocalStandardDart::validateCurrentState()
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

int LocalStandardDart::validateInput(const int &pointValue)
{
    if((pointValue < 0 || pointValue > 20) && (pointValue != 25 || pointValue != 50))
        return InvalidDomain;

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

int LocalStandardDart::currentTurnIndex()
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
    auto pointIds = dataContext()->playerPoints(currentTournament(),currentActivePlayer());

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

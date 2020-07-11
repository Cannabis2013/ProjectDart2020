#include "localfirsttopost.h"

int LocalFirstToPost::start()
{
    _isActive = true;
    if(_roundIndex == 0){
        dataContext()->addRound(currentTournament(),++_roundIndex);
        dataContext()->addSet(currentTournament(),_roundIndex,_setIndex);
    }
    _currentStatus = GameStatus::Running;
    return _currentStatus;
}

int LocalFirstToPost::stop()
{
    _isActive = false;
    _currentStatus = GameStatus::Idle;
    return _currentStatus;
}

int LocalFirstToPost::processInput(const int &point)
{
    if(status() == (Idle | WinnerDeclared))
        return status();

    // Evaluate input according to point domain and aggregated sum domain
    auto inputResponse = validateInput(point);

    if(inputResponse == InputPointDomain::InvalidDomain)
        throw INVALID_DOMAIN;
    if(inputResponse == AggregatedSumDomains::PointDomain)
    {
        // Update datacontext
        addPoint(point);
    }
    else if(inputResponse == AggregatedSumDomains::CriticalDomain)
    {
        addPoint(point);
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

QString LocalFirstToPost::calculateThrowSuggestion()
{
    /* TODO: Here you first have to develop an algorithm to help assess the various combinations that exists after the player reach the 180 points threshold
     * TODO: When done, ruct a string containing the various suggestions. Ex.: 'T20,D10,5' or 'D5,1' for a remaining score at 95 or 11 respectively.
     */

    auto legCount = dataContext()->tournamentNumberOfLegs(currentTournament());

    auto remainingScore = _keyPoint - sum();

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
    return _legIndex;
}

QUuid LocalFirstToPost::currentTournament()
{
    return _tournament;
}

void LocalFirstToPost::setCurrentTournament(QUuid &tournament)
{
    _tournament = tournament;
    auto players = _dataContext->tournamentAssignedPlayers(tournament);
    auto keyPoint = _dataContext->tournamentKeyPoint(tournament);
    _keyPoint = keyPoint;
    auto legs = _dataContext->tournamentNumberOfLegs(tournament);
    _numberOfLegs = legs;
    _assignedPlayers = players;
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
    if(_legIndex > 0)
    {
        _legIndex--;

        return _assignedPlayers.value(_setIndex);
    }

    _legIndex = 2;

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

    if(_legIndex < _numberOfLegs)
        _legIndex++;
    else
        _legIndex = 0;

    if(_setIndex == lastPlayerIndex())
    {
        _setIndex = 0;
        _roundIndex++;
    }
    else
    {
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

int LocalFirstToPost::score(const QUuid &player)
{
    auto playerScore = _dataContext->playerPoints(currentTournament(),player);
    int totalScore = _keyPoint;
    for (auto scoreID : playerScore) {
        auto point = _dataContext->pointValue(scoreID);
        totalScore -= point;
    }
    return totalScore;
}

void LocalFirstToPost::setDataContext(DefaultDataInterface *dataContext)
{
    _dataContext = dataContext;
}

DefaultDataInterface *LocalFirstToPost::dataContext()
{
    return _dataContext;
}

int LocalFirstToPost::validateCurrentState()
{
    auto playerSum = _keyPoint - sum();

    if(playerSum > criticalLimit)
        return PointDomain;
    else if(playerSum <= criticalLimit && playerSum > 0)
        return CriticalDomain;
    else if(playerSum == 0)
        return TargetDomain;
    else
        return OutsideDomain;
}

int LocalFirstToPost::validateInput(const int &pointValue)
{
    auto playerScore = _keyPoint - sum(pointValue);

    if(playerScore > criticalLimit)
        return PointDomain;
    else if(playerScore <= criticalLimit && playerScore > 0)
        return CriticalDomain;
    else if(playerScore == 0)
        return TargetDomain;
    else
        return OutsideDomain;
}

QUuid LocalFirstToPost::addPoint(const int &point)
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

    if(_turnIndex % _numberOfLegs == 0)
    {
        _setIndex++;
        _legIndex = 0;
        if(_setIndex >= _assignedPlayers.count()){
            dataContext()->addRound(currentTournament(),++_roundIndex);
            _setIndex = 0;
        }

        dataContext()->addSet(currentTournament(),currentRoundIndex(),_setIndex);
    }
    else
    {
        _legIndex++;
    }
}

int LocalFirstToPost::sum(const int &pointValue)
{
    auto pointIds = _dataContext->playerPoints(_tournament,currentActivePlayer());

    int sum = pointValue;

    for (auto pointId : pointIds)
        sum += _dataContext->pointValue(pointId);

    return sum;
}

int LocalFirstToPost::sum(const QUuid &player)
{
    auto pointIds = _dataContext->playerPoints(_tournament,player);

    int sum = 0;
    for (auto pointId : pointIds)
        sum += _dataContext->pointValue(pointId);

    return sum;
}

int LocalFirstToPost::sum()
{
    auto pointIds = dataContext()->playerPoints(currentTournament(),currentActivePlayer());

    int sum = 0;
    for (auto pointId : pointIds)
        sum += _dataContext->pointValue(pointId);

    return sum;
}

void LocalFirstToPost::declareWinner()
{
    _winner = currentActivePlayer();
    _isActive = false;
    _currentStatus = WinnerDeclared;
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

DefaultControllerInterface *LocalFirstToPost::setPointLogisticInterface(IPointLogisticManager<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void LocalFirstToPost::consistencyCheck()
{
    Q_UNIMPLEMENTED();
}

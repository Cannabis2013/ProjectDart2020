#include "localfirsttopost.h"

int LocalFirstToPost::start()
{
    _isActive = true;
    if(_roundIndex == 0){
        dataContext()->addRound(currentTournamentID(),++_roundIndex);
        dataContext()->addSet(currentTournamentID(),_roundIndex,_setIndex);
    }
    _currentStatus = GameStatus::GameControllerRunning;
    emit sendStatus(GameStatus::GameControllerAwaitsInput,"");
    return _currentStatus;
}

int LocalFirstToPost::stop()
{
    _isActive = false;
    _currentStatus = GameStatus::GameControllerIdle;
    return _currentStatus;
}

int LocalFirstToPost::processInput(const int &point)
{
    if(status() == (GameControllerIdle | GameControllerWinnerDeclared))
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
    emit sendStatus(GameStatus::GameControllerAwaitsInput,"");
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

QString LocalFirstToPost::calculateThrowSuggestion()
{
    /* TODO: Here you first have to develop an algorithm to help assess the various combinations that exists after the player reach the 180 points threshold
     * TODO: When done, ruct a string containing the various suggestions. Ex.: 'T20,D10,5' or 'D5,1' for a remaining score at 95 or 11 respectively.
     */

    auto legCount = dataContext()->tournamentNumberOfThrows(currentTournamentID());

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
    return _throwIndex;
}

QUuid LocalFirstToPost::currentTournamentID()
{
    return _tournament;
}

void LocalFirstToPost::setCurrentTournament(QUuid &tournament)
{
    _tournament = tournament;
    initializeController(tournament);
    initializeIndexes(tournament);
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

int LocalFirstToPost::score(const QUuid &player)
{
    auto playerScore = dataContext()->playerPoints(currentTournamentID(),player, 0x2);
    int totalScore = _keyPoint;
    for (auto scoreID : playerScore) {
        auto point = dataContext()->pointValue(scoreID);
        totalScore -= point;
    }
    return totalScore;
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
    auto score = _keyPoint - sum(point);
    auto playerID = currentActivePlayer();
    auto tournamentID = currentTournamentID();
    auto roundIndex = currentRoundIndex();
    auto setIndex = currentPlayerIndex();
    auto legIndex = currentLegIndex();

    auto pointID = dataContext()->addScore(tournamentID,
                                           playerID,
                                           roundIndex,
                                           setIndex,
                                           legIndex,
                                           point,
                                           score);
    return pointID;
}

void LocalFirstToPost::initializeController(const QUuid &tournament)
{
    _keyPoint = dataContext()->tournamentKeyPoint(tournament);
    _numberOfThrows = dataContext()->tournamentNumberOfThrows(tournament);
    _assignedPlayers = dataContext()->tournamentAssignedPlayers(tournament);
}

void LocalFirstToPost::initializeIndexes(const QUuid &tournament)
{
    auto turnIndex = 0;
    auto roundIndex = 1;
    auto setIndex = 0;
    auto legIndex = 0;
    auto playersCount = _assignedPlayers.count();
    auto numberOfLegs = _numberOfThrows;
    while(1)
    {
        auto playerID = _assignedPlayers.at(setIndex);
        try {
            dataContext()->playerPoint(tournament,playerID,roundIndex,legIndex,DisplayHint);
        } catch (const char *msg) {
            break;
        }
        if(++legIndex % numberOfLegs == 0)
        {
            legIndex = 0;
            setIndex++;
            if(setIndex >= playersCount)
            {
                roundIndex++;
                setIndex = 0;
            }
        }
        turnIndex++;
    }
    _roundIndex = turnIndex == 0 ? 0 : roundIndex;
    _setIndex = turnIndex == 0 ? 0 : setIndex;
    _throwIndex = turnIndex == 0 ? 0 : legIndex;
    _turnIndex = turnIndex == 0 ? 0 : turnIndex;
    _totalTurns = turnIndex == 0 ? 0 : dataContext()->playerPointsCount(allHints);
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
            dataContext()->addRound(currentTournamentID(),++_roundIndex);
            _setIndex = 0;
        }

        dataContext()->addSet(currentTournamentID(),currentRoundIndex(),_setIndex);
    }
    else
    {
        _throwIndex++;
    }
}

int LocalFirstToPost::sum(const int &pointValue)
{
    auto pointIds = dataContext()->playerPoints(_tournament,currentActivePlayer(),DisplayHint);

    int sum = pointValue;

    for (auto pointId : pointIds)
        sum += dataContext()->pointValue(pointId);

    return sum;
}

int LocalFirstToPost::sum(const QUuid &player)
{
    auto pointIds = dataContext()->playerPoints(_tournament,player,DisplayHint);

    int sum = 0;
    for (auto pointId : pointIds)
        sum += dataContext()->pointValue(pointId);

    return sum;
}

int LocalFirstToPost::sum()
{
    auto pointIds = dataContext()->playerPoints(currentTournamentID(),currentActivePlayer(),DisplayHint);

    int sum = 0;
    for (auto pointId : pointIds)
        sum += dataContext()->pointValue(pointId);

    return sum;
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

AbstractControllerInterface *LocalFirstToPost::setPointLogisticInterface(IPointLogisticManager<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void LocalFirstToPost::consistencyCheck()
{
    Q_UNIMPLEMENTED();
}
#include "dartsturnvalues.h"

DartsTurnValues::DartsTurnValues(IDartsPlayers* players, IDartsIndexes* _indexes, IDartsStatistics* statistics, IDartsFinishes* finishes, IDartsScores* scores)
    : _players(players)
    , _indexes(_indexes)
    , _statistics(statistics)
    , _finishes(finishes)
    , _scores(scores)
{}

TurnInfo DartsTurnValues::currentTurnInfo()
{
        TurnInfo turnInfo;
        updateWithIndexes(turnInfo);
        updateWithPlayerName(turnInfo);
        updateWithStatistics(turnInfo);
        updateWithFinish(turnInfo);
        return turnInfo;
}

void DartsTurnValues::updateWithIndexes(TurnInfo& turnInfo)
{
        turnInfo.setTurnIndex(_indexes->turnIndex());
        turnInfo.setCanUndo(_indexes->canUndo());
        turnInfo.setCanRedo(_indexes->canRedo());
}

void DartsTurnValues::updateWithStatistics(TurnInfo& turnInfo)
{
        turnInfo.setAverage(_statistics->average());
        turnInfo.setLow(_statistics->lowest());
        turnInfo.setHigh(_statistics->highest());
}

void DartsTurnValues::updateWithPlayerName(TurnInfo& turnInfo)
{
        auto playerName = _players->name();
        turnInfo.setCurrentPlayer(playerName);
}

void DartsTurnValues::updateWithFinish(TurnInfo& turnInfo)
{
        auto score = _scores->score().playerScore();
        auto legIndex = _indexes->index().legIndex();
        auto finish = _finishes->suggestTargetRow(score, legIndex);
        turnInfo.setFinish(finish);
}

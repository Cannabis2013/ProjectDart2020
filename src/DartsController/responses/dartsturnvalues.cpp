#include "dartsturnvalues.h"

DartsTurnValues::DartsTurnValues(IDartsPlayers* players, IDartsIndexes* _indexes, IDartsStatistics* statistics, IDartsFinishes* finishes, IDartsScores* scores, IDartsStatus* status)
    : _players(players)
    , _indexes(_indexes)
    , _statistics(statistics)
    , _finishes(finishes)
    , _scores(scores)
    , _status(status)
{}

TurnInfo DartsTurnValues::currentTurnInfo()
{
        TurnInfo turnInfo;
        updateWithIndexes(turnInfo);
        updateWithPlayerName(turnInfo);
        updateWithStatistics(turnInfo);
        updateWithFinish(turnInfo);
        updateWithStatus(turnInfo);
        return turnInfo;
}

void DartsTurnValues::updateWithIndexes(TurnInfo& turnInfo)
{
        turnInfo.setTurnIndex(_indexes->index().throwIndex());
        turnInfo.setCanUndo(_indexes->canUndo());
        turnInfo.setCanRedo(_indexes->canRedo());
}

void DartsTurnValues::updateWithStatistics(TurnInfo& turnInfo)
{
        auto stats = _statistics->statistics();
        turnInfo.setAverage(stats.average);
        turnInfo.setLow(stats.low);
        turnInfo.setHigh(stats.high);
}

void DartsTurnValues::updateWithPlayerName(TurnInfo& turnInfo)
{
        auto playerName = _players->name();
        turnInfo.setCurrentPlayer(playerName);
}

void DartsTurnValues::updateWithFinish(TurnInfo& turnInfo)
{
        auto score = _scores->score().playerScore();
        auto legIndex = _indexes->index().turnIndex();
        auto finish = _finishes->suggestTargetRow(score, legIndex);
        turnInfo.setFinish(finish);
}

void DartsTurnValues::updateWithStatus(TurnInfo& turnInfo)
{
        turnInfo.setStatus(_status->status());
}

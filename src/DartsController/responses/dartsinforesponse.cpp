#include "dartsinforesponse.h"

DartsInfoResponse::DartsInfoResponse(IDartsScores* scores, IDartPlayers* players, IDartIndexes* _indexes) :
        _scores(scores),
        _players(players),
        _indexes(_indexes)
{}

InitialValueInfo DartsInfoResponse::initialInfo()
{
        auto playerNames = _players->names();
        auto playerScores = _scores->scores();
        return InitialValueInfo(playerNames,playerScores);
}

TurnInfo DartsInfoResponse::currentTurnInfo()
{
        auto dartIndexes = _indexes->index();
        auto playerName = _players->name(dartIndexes.playerIndex());
        auto score = _scores->score();
        return TurnInfo(playerName,score);
}

WinnerInfo DartsInfoResponse::winnerInfo()
{
        auto dartIndexes = _indexes->index();
        auto playerName = _players->name(dartIndexes.playerIndex());
        return WinnerInfo(playerName);
}
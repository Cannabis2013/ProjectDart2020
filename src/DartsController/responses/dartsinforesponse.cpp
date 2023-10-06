#include "dartsinforesponse.h"

DartsInfoResponse::DartsInfoResponse(IDartsScores* scores, IDartPlayers* players, IDartsIndexes* _indexes) :
        _scores(scores),
        _players(players),
        _indexes(_indexes)
{}

TurnInfo DartsInfoResponse::currentTurnInfo()
{
        auto dartIndexes = _indexes->index();
        auto canUndo = _indexes->canUndo();
        auto canRedo = _indexes->canRedo();
        auto playerName = _players->name(dartIndexes.playerIndex());
        return TurnInfo(playerName,canUndo,canRedo);
}

WinnerInfo DartsInfoResponse::winnerInfo()
{
        auto dartIndexes = _indexes->index();
        auto playerName = _players->name(dartIndexes.playerIndex());
        return WinnerInfo(playerName);
}

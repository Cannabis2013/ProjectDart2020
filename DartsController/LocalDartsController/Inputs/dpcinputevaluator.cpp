#include "dpcinputevaluator.h"

#include <DartsController/Contracts/Models/dcinput.h>
#include <DartsController/Contracts/Models/dcmeta.h>
#include <DartsController/Contracts/Models/dcplayer.h>

void DPCInputEvaluator::evaluate(DCInput &input, DCMeta *meta, const DCPlayer &player)
{
    auto scoreCand = calcScore(input.score,player.remaining);
    if(!player.in && meta->entryRestricted)
        playerHasNotEntered(input,scoreCand,meta);
    else
        playerHasEntered(input,meta,scoreCand);
}

void DPCInputEvaluator::playerHasNotEntered(DCInput &input, const int &scoreCand, DCMeta *meta)
{
    if(input.modKeyCode == DoubleModifier)
        updateInputDetails(scoreCand,true,input,meta);
    else
        nullifyInput(input,meta);
}

void DPCInputEvaluator::playerHasEntered(DCInput &input, DCMeta *meta, const int &scoreCand)
{
    if(scoreCand >= minimumAllowedScore)
        updateInputDetails(scoreCand,true,input,meta);
    else if(scoreCand == 0 && (input.modKeyCode == DoubleModifier || input.score == _bullsEye))
        updateWinnerDetails(input,meta);
    else
        nullifyInput(input,meta);
}

void DPCInputEvaluator::updateWinnerDetails(DCInput &input, DCMeta *meta)
{
    updateInputDetails(0,true,input,meta);
    meta->winnerName = input.playerName;
    meta->status = WinnerDeclared;
}

int DPCInputEvaluator::calcScore(const int &scoreCand, const int &remScore)
{
    auto totalScoreCandidate = remScore - scoreCand;
    if(totalScoreCandidate < 0)
        return remScore;
    return totalScoreCandidate;
}

void DPCInputEvaluator::updateInputDetails(const int &remaining, const bool &inGame, DCInput &input, DCMeta *meta)
{
    input.remScore = remaining;
    input.inGame = inGame;
    meta->lastInput = input;
}

void DPCInputEvaluator::nullifyInput(DCInput &input, DCMeta *meta)
{
    input.score = 0;
    meta->lastInput = input;
}

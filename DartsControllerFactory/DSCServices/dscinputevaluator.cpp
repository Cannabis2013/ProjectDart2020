#include "dscinputevaluator.h"
#include "ServicesProvider/dcservices.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
#include "Models/dcmeta.h"

DCMeta DSCInputEvaluator::evaluate(DCInput &input, const DCMeta &meta, const DCPlayer &player)
{
    auto m = meta;
    auto score = calcScore(input.score,player.remScore);
    update(score,input,m);
    return m;
}

int DSCInputEvaluator::calcScore(const int &scoreCand, const int &remScore)
{
    auto totalScoreCandidate = remScore - scoreCand;
    if(totalScoreCandidate < 0)
        return remScore;
    return totalScoreCandidate;
}


void DSCInputEvaluator::update(const int &scoreCand, DCInput &input, DCMeta &meta)
{
    if(scoreCand >= minimumAllowedScore)
        updateInputDetails(scoreCand,input,meta);
    else if(scoreCand == 0)
        updateWinnerDetails(input,meta);
    else
        nullifyInput(input,meta);
}

void DSCInputEvaluator::updateInputDetails(const int &scoreCand,DCInput &input, DCMeta &meta)
{
    input.approved = true;
    input.remScore = scoreCand;
    meta.lastInput = input;
}

void DSCInputEvaluator::nullifyInput(DCInput &input, DCMeta &meta)
{
    input.score = 0;
    meta.lastInput = input;
}

void DSCInputEvaluator::updateWinnerDetails(DCInput &input, DCMeta &meta)
{
    updateInputDetails(0,input,meta);
    meta.winnerName = input.playerName;
    meta.status = WinnerDeclared;
    meta.lastInput = input;
}

#include "dscinputevaluator.h"

DSCInputEvaluator::DSCInputEvaluator(DCServices *services) : _services(services){}

void DSCInputEvaluator::eval(DCInput &input)
{
    auto meta = &_services->metaService()->meta();
    auto idx = _services->indexService()->index();
    auto player = _services->playerService()->player(idx.playerIndex);
    auto score = calcScore(input.score,player.remScore);
    update(score,input,meta);
}

int DSCInputEvaluator::calcScore(const int &scoreCand, const int &remScore)
{
    auto totalScoreCandidate = remScore - scoreCand;
    if(totalScoreCandidate < 0)
        return remScore;
    return totalScoreCandidate;
}

void DSCInputEvaluator::update(const int &scoreCand, DCInput &input, DCMeta *meta)
{
    if(scoreCand >= minimumAllowedScore)
    {
        input.approved = true;
        input.remScore = scoreCand;
    }
    else if(scoreCand == 0)
    {
        input.approved = true;
        input.remScore = 0;
        meta->winnerName = input.playerName;
        meta->status = WinnerDeclared;
    }
    else
    {
        input.score = 0;
    }
}

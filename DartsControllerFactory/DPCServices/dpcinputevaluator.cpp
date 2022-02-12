#include "dpcinputevaluator.h"

DPCInputEvaluator::DPCInputEvaluator(DCServices *services) : _services(services){}

void DPCInputEvaluator::evaluate(DCInput &input)
{
    auto meta = &_services->metaService()->meta();
    auto idx = _services->indexController()->index();
    auto player = _services->playerManager()->player(idx.playerIndex);
    auto scoreCand = calcScore(input.score,player.remScore);
    if(!player.in && meta->entryRestricted)
        playerHasNotEntered(input,scoreCand);
    else
        playerHasEntered(input,meta,scoreCand);
}

void DPCInputEvaluator::playerHasNotEntered(DCInput &input, const int &scoreCand)
{
    if(input.modKeyCode == DoubleModifier)
    {
        input.remScore = scoreCand;
        input.inGame = true;
    }
    else
    {
        input.score = 0;
    }
}

void DPCInputEvaluator::playerHasEntered(DCInput &ipt, DCMeta *meta, const int &scoreCand)
{
    if(scoreCand >= minimumAllowedScore)
        ipt.remScore = scoreCand;
    else if(scoreCand == 0 && (ipt.modKeyCode == DoubleModifier || ipt.score == _bullsEye))
        setWinnerValues(ipt,meta);
    else
        ipt.score = 0;
}

void DPCInputEvaluator::setWinnerValues(DCInput &ipt, DCMeta *meta)
{
    ipt.remScore = 0;
    meta->winnerName = ipt.playerName;
    meta->status = WinnerDeclared;
}

int DPCInputEvaluator::calcScore(const int &scoreCand, const int &remScore)
{
    auto totalScoreCandidate = remScore - scoreCand;
    if(totalScoreCandidate < 0)
        return remScore;
    return totalScoreCandidate;
}

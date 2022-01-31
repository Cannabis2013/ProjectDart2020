#include "dpcinputevaluator.h"

DPCInputEvaluator::DPCInputEvaluator(DCServices *services) : _services(services){}

void DPCInputEvaluator::eval(DCInput &input)
{
    auto meta = &_services->metaService()->meta();
    auto idx = _services->indexService()->index();
    auto player = _services->playerService()->player(idx.playerIndex);
    auto scoreCand = _services->scoreCalc()->calc(input.score,player.remScore);
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

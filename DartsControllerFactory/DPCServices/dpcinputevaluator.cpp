#include "dpcinputevaluator.h"

DPCInputEvaluator::DPCInputEvaluator(DCServices *services)
{
    _metaManager = services->metaServices()->metaManager();
    _playerManager = services->playerServices()->playerManager();
    _indexController = services->indexServices()->indexController();
}

void DPCInputEvaluator::evaluate(DCInput &input)
{
    auto meta = &_metaManager->meta();
    auto idx = _indexController->index();
    auto player = _playerManager->player(idx.playerIndex);
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
    meta->status = _metaManager->WinnerDeclared;
}

int DPCInputEvaluator::calcScore(const int &scoreCand, const int &remScore)
{
    auto totalScoreCandidate = remScore - scoreCand;
    if(totalScoreCandidate < 0)
        return remScore;
    return totalScoreCandidate;
}

#include "dscinputevaluator.h"
#include "ServicesProvider/dcservices.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
#include "Models/dcmeta.h"

DSCInputEvaluator::DSCInputEvaluator(DCServices *services)
{
    _metaManager = services->metaServices()->metaManager();
    _playerManager = services->playerServices()->playerManager();
    _indexController = services->indexServices()->indexController();
}

void DSCInputEvaluator::evaluate(DCInput &input)
{
    auto meta = &_metaManager->meta();
    auto idx = _indexController->index();
    auto player = _playerManager->player(idx.playerIndex);
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
        meta->status = _metaManager->WinnerDeclared;
    }
    else
    {
        input.score = 0;
    }
}

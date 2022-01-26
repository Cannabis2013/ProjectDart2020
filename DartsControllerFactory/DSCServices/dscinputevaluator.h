#ifndef DSCINPUTEVALUATOR_H
#define DSCINPUTEVALUATOR_H
#include "DCInputSLAs/idcipteval.h"
#include "Models/dcinput.h"
#include "Models/dcplayer.h"
#include "Models/dcmeta.h"
#include "ServicesProvider/dcservices.h"
class DSCInputEvaluator : public IDCIptEval
{
public:
    enum ControllerState {
        Initialized,
        Running,
        WinnerDeclared,
        AwaitsInput
    };
    DSCInputEvaluator(DCServices *services) : _services(services){}
    void eval(DCInput &input) override
    {
        auto meta = _services->metaService()->meta();
        auto idx = _services->indexService()->index();
        auto player = _services->plaCtx()->player(idx.playerIndex);
        auto scoreCand = _services->scoreCalc()->calc(input.score,player.remScore);
        update(scoreCand,input,meta);
    }
private:
    void update(const int &scoreCand, DCInput &input, DCMeta &meta)
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
            updateWinnerMeta(input,meta,WinnerDeclared);
        }
        else
        {
            input.score = 0;
        }
    }
    void updateWinnerMeta(DCInput &input, DCMeta &meta, const int &winnerStatus) const
    {
        meta.winnerName = input.playerName;
        meta.status = winnerStatus;
    }
    const int minimumAllowedScore = 2;
    DCServices *_services;
};
#endif // SCOREVALIDATOR_H

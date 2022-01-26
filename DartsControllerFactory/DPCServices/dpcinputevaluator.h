#ifndef DPCINPUTVALIDATOR_H
#define DPCINPUTVALIDATOR_H
#include "DCInputSLAs/idcipteval.h"
#include "Models/dcmeta.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"

#include "ServicesProvider/dcservices.h"
class DPCInputEvaluator : public IDCIptEval
{
    Q_OBJECT
public:
    enum ControllerState {
        Initialized,
        Running,
        WinnerDeclared,
        AwaitsInput
    };
    DPCInputEvaluator(DCServices *services) : _services(services){}
    void eval(DCInput &input) override
    {
        auto meta = _services->metaService()->meta();
        auto idx = _services->indexService()->index();
        auto player = _services->plaCtx()->player(idx.playerIndex);
        auto scoreCand = _services->scoreCalc()->calc(input.score,player.remScore);
        if(!player.in && meta.entryRestricted)
            playerHasNotEntered(input,scoreCand);
        else
            playerHasEntered(input,meta,scoreCand);
    }
private:
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C
    };
    void playerHasNotEntered(DCInput &ipt, const int &scoreCand)
    {
        if(ipt.modKeyCode == DoubleModifier)
        {
            ipt.remScore = scoreCand;
            ipt.inGame = true;
        }
        else
        {
            ipt.score = 0;
        }
    }
    void playerHasEntered(DCInput &ipt, DCMeta &meta,const int &scoreCand)
    {
        if(scoreCand >= minimumAllowedScore)
            ipt.remScore = scoreCand;
        else if(scoreCand == 0 && (ipt.modKeyCode == DoubleModifier || ipt.score == _bullsEye))
            setWinnerValues(ipt,meta);
        else
            ipt.score = 0;
    }
    void setWinnerValues(DCInput &ipt, DCMeta &meta)
    {
        ipt.remScore = 0;
        meta.winnerName = ipt.playerName;
        meta.status = WinnerDeclared;
    }
    const int _bullsEye = 50;
    const int minimumAllowedScore = 2;
    DCServices *_services;
};
#endif // POINTVALIDATOR_H

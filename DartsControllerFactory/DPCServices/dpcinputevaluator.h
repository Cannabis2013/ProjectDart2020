#ifndef DPCINPUTVALIDATOR_H
#define DPCINPUTVALIDATOR_H
#include "DCInputSLAs/idcipteval.h"
#include "Models/dcmeta.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
class DPCInputEvaluator : public IDCIptEval
{
    Q_OBJECT
public:
    void eval(DCInput &input, const int &scoreCand, DCMeta &meta, const DCPlayer &player, const int &winnerStatus) override
    {
        if(!player.in && meta.entryRestricted)
            playerHasNotEntered(input,scoreCand);
        else
            playerHasEntered(input,meta,scoreCand,winnerStatus);
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
    void playerHasEntered(DCInput &ipt, DCMeta &meta,const int &scoreCand, const int &winnerStatus)
    {
        if(scoreCand >= minimumAllowedScore)
            ipt.remScore = scoreCand;
        else if(scoreCand == 0 && (ipt.modKeyCode == DoubleModifier || ipt.score == _bullsEye))
            setWinnerValues(ipt,meta,winnerStatus);
        else
            ipt.score = 0;
    }
    void setWinnerValues(DCInput &ipt, DCMeta &meta, const int &winnerStatus)
    {
        ipt.remScore = 0;
        meta.winnerName = ipt.playerName;
        meta.status = winnerStatus;
    }
    const int _bullsEye = 50;
    const int minimumAllowedScore = 2;
};
#endif // POINTVALIDATOR_H

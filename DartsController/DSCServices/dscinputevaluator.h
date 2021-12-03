#ifndef DSCINPUTEVALUATOR_H
#define DSCINPUTEVALUATOR_H
#include "DartsController/DPCServices/dpcinputevaluator.h"
class DSCInputEvaluator : public AbstractDCInputEvaluator
{
public:
    static DSCInputEvaluator *createInstance()
    {
        return new DSCInputEvaluator();
    }
    virtual QByteArray evaluate(DCIptVals &input, const int &scoreCand, IDCMetaCtx *metaInfo, AbstractDartsCtrl *controller,
                                const IDartsStatusCodes *statusCodes, IDCPlayerCtx *) override
    {
        QByteArray byteArray;
        if(scoreCand >= minimumAllowedScore)
        {
            input.approved = true;
            input.remainingScore = scoreCand;
            byteArray = controller->addInputToModelsContext(input);
        }
        else if(scoreCand == 0)
        {
            input.approved = true;
            input.remainingScore = 0;
            updateWinnerMeta(input,metaInfo,statusCodes);
            byteArray = controller->addInputToModelsContext(input);
        }
        else
        {
            input.score = 0;
            byteArray = controller->addInputToModelsContext(input);
        }
        return byteArray;
    }
private:
    void updateWinnerMeta(DCIptVals &input, IDCMetaCtx *metaInfo, const IDartsStatusCodes *statusCodes) const
    {
        metaInfo->get().winnerId = input.playerId;
        metaInfo->get().winnerName = input.playerName;
        metaInfo->get().status = statusCodes->winnerFound();
    }
    const int minimumAllowedScore = 2;
};
#endif // SCOREVALIDATOR_H
